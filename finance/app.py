import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd


# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Get the symbols and sum of shares from the DB
    table = db.execute("SELECT symbol, SUM(shares) FROM buys WHERE user_id = ? GROUP BY symbol", session["user_id"])

    # Get the current price for each symbol in the table
    for stock in table:
        priceApi = lookup(stock["symbol"])
        price = priceApi["price"]
        stock["price"] = price

    # Get current cash
    cashList = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    # this returns a lst with a dictionary inside that uses the key "cash" and has the cash number as the value
    cash = cashList[0]["cash"]

    # Get total
    total = 0;
    for stock in table:
        total += stock["price"] * stock["SUM(shares)"]

    total += cash

    return render_template("index.html", table=table, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Access form data
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Please add a symbol")

        priceApi = lookup(symbol)
        if priceApi == None:
            return apology("Invalid symbol. Try again")

        shares = request.form.get("shares")
        if not shares:
            return apology("Please add a share amount.")
        try:
            shares = int(shares)
        except ValueError:
            return apology("Invalid shares number. Try again.")
        if shares < 1:
            return apology("Invalid shares number. Try again.")

        # Check if the user has enough money for the purchase
        cashList = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        # this returns a lst with a dictionary inside that uses the key "cash" and has the cash number as the value
        cash = cashList[0]["cash"]

        price = priceApi["price"]

        cash = cash - (price * shares)

        if cash < 0:
            return apology("Insufficient funds")

        # Get date
        current_datetime = datetime.now()
        date = f"{current_datetime.strftime('%Y-%m-%d %H:%M:%S')}"

   	    # Record de purchase in buys table
        db.execute("INSERT INTO buys (user_id, symbol, price, shares, date) VALUES (?, ?, ?, ?, ?)", session["user_id"], symbol, price, shares, date)

        # Update the cash the user has
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])

        return redirect("/")
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # SELECT the complete buys table
    operations = db.execute("SELECT * FROM buys")

    return render_template("history.html", operations=operations)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get(
                "username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Access form data
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Please add a symbol")

        price = lookup(symbol)
        if price == None:
            return apology("Invalid symbol. Try again")

        return render_template("quoted.html", price=price)
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Access form data
        username = request.form.get("username")
        if not username:
            return apology("Please add a username")

        password = request.form.get("password")
        if not password:
            return apology("Please add a password")

        confirmation = request.form.get("confirmation")
        if not confirmation:
            return apology("Please confirm password")

        if not password == confirmation:
            return apology("Password and confirmation are different. Try again.")

        # Generate hash password
        hash = generate_password_hash(password)

        # Insert data into database
        try:
            db.execute(
            "INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)
        except ValueError:
            return apology("This user already exists. Try logging in.")

        # Redirect user to home page
        return redirect("/")
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Access form data
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Please add a symbol")

        # Get the symbols and sum of shares from the DB
        table = db.execute("SELECT symbol, SUM(shares) FROM buys WHERE user_id = ? GROUP BY symbol", session["user_id"])

        shares = request.form.get("shares")
        if not shares:
            return apology("Please add a share amount.")
        try:
            shares = int(shares)
        except ValueError:
            return apology("Invalid shares number. Try again.")
        if shares < 1:
            return apology("Invalid shares number. Try again.")

        # check if the user has stocks from that symbol and sufficient amount
        for row in table:
            # if the user does not own that many shares of the stock.
            if row["symbol"] == symbol:
                if row["SUM(shares)"] >= shares:
                    break
                else:
                    return apology("You do not own enough stocks for that symbol. Try again")
        # if the user does not own any shares of that stock.
        else:
            return apology("You do not own this stock. Try again")

        # Look up the amount of cash before sell
        cashList = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        # this SELECT returns a list with a dictionary inside that uses the key "cash" and has the cash number as the value
        cash = cashList[0]["cash"]

        # check the price od the stock
        priceApi = lookup(symbol)
        price = priceApi["price"]

        # The new amount of cash the user will have after the sell
        cash = cash + (price * shares)

        # change shares to negative shares
        shares *= (-1)

        # Get date
        current_datetime = datetime.now()
        date = f"{current_datetime.strftime('%Y-%m-%d %H:%M:%S')}"

   	    # Record de purchase in buys table
        db.execute("INSERT INTO buys (user_id, symbol, price, shares, date) VALUES (?, ?, ?, ?, ?)", session["user_id"], symbol, price, shares, date)

        # Update the cash the user has
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])

        return redirect("/")
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        # Get the symbols and sum of shares from the DB
        table = db.execute("SELECT symbol, SUM(shares) FROM buys WHERE user_id = ? GROUP BY symbol", session["user_id"])
        return render_template("sell.html", table=table)


@app.route("/addcash", methods=["GET", "POST"])
@login_required
def addcash():
    """Add cash to the account"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Access form data
        cash = request.form.get("cash")
        if not cash:
            return apology("Please add an amount of cash")
        try:
            cash = float(cash)
        except ValueError:
            return apology("Invalid cash number. Try again.")
        if cash <= 0:
            return apology("Invalid cash number. Try again.")

        # Look up the amount of cash before sell
        cashList = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        # this SELECT returns a list with a dictionary inside that uses the key "cash" and has the cash number as the value
        cashBefore = cashList[0]["cash"]

        # The new amount of cash the user will have after adding
        cash += cashBefore

        # Update the cash the user has
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])

        return redirect("/")
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("addcash.html")
