import turtle

# Vairables 
win_h=600 # windown height
win_w=800 # window width

speed_dx = 0.3 # speed in X direction
speed_dy = 0.3 # speed in Y direction

# Setting Up Main Window 
win = turtle.Screen()
win.title("PONG!")
win.bgcolor("black")
win.setup(width=win_w,height=win_h)
win.tracer(0)

# Setting Up the main components | left right pads and ball
pad_left = turtle.Turtle()
pad_left.speed(0)
pad_left.shape("square")
pad_left.color("white")
pad_left.shapesize(stretch_wid=5,stretch_len=1)
pad_left.penup()
pad_left.goto(-350,0)

pad_right = turtle.Turtle()
pad_right.speed(0)
pad_right.shape("square")
pad_right.color("white")
pad_right.shapesize(stretch_wid=5,stretch_len=1)
pad_right.penup()
pad_right.goto(350,0)

ball = turtle.Turtle()
ball.speed(0)
ball.shape("square")
ball.color("white")
ball.penup()
ball.goto(0,0)
ball.dx=speed_dx
ball.dy=speed_dy

# Initial values for Scores of each players
score_left = 0
score_right = 0

# To Write Scores on Screen
pen = turtle.Turtle()
pen.speed(0)
pen.color("white")
pen.penup()
pen.hideturtle()
pen.goto(0,260)
pen.write(str(score_left)+"-"+str(score_right),align="center",font=("Monospace", 28, "normal"))

def pad_left_up():
    y = pad_left.ycor()
    y+=20
    pad_left.sety(y)

def pad_left_down():
    y = pad_left.ycor()
    y-=20
    pad_left.sety(y)

def pad_right_up():
    y = pad_right.ycor()
    y+=20
    pad_right.sety(y)

def pad_right_down():
    y = pad_right.ycor()
    y-=20
    pad_right.sety(y)

win.listen()

# Moving the PADS up/down on keypress
win.onkeypress(pad_left_up,"w")    
win.onkeypress(pad_left_down,"s")

win.onkeypress(pad_right_up,"Up")
win.onkeypress(pad_right_down,"Down")

while True: 
    win.update()

    ball.setx(ball.xcor() + ball.dx)
    ball.sety(ball.ycor() + ball.dy)

    # Bouncing At Top and Bottom | Changing the direction
    dim_y = (win_h//2)-10
    if ball.ycor() > dim_y:
        ball.sety(dim_y)
        ball.dy *= -1
    if ball.ycor() < -dim_y:
        ball.sety(-dim_y)
        ball.dy *= -1
    
    # Bouncing At Right and Left | Relaunching from center 
    dim_x = (win_w//2)-10
    if ball.xcor() > dim_x: 
        ball.goto(0,0)
        ball.dx *= -1
        score_left+=1
        pen.clear()
        pen.write(str(score_left)+"-"+str(score_right),align="center",font=("Monospace", 28, "normal"))
        
    if ball.xcor() < -dim_x:
        ball.goto(0,0)
        ball.dx *= 1
        score_right+=1
        pen.clear()
        pen.write(str(score_left)+"-"+str(score_right),align="center",font=("Monospace", 28, "normal"))

    
    # Bouncing from pad_left and pad_right
    if (ball.xcor() > 340 and ball.xcor() < 350) and (ball.ycor() < pad_right.ycor() + 28 and ball.ycor() > pad_right.ycor() - 40 ):
        ball.setx(340)
        ball.dx *= -1
    if (ball.xcor() < -340 and ball.xcor() > -350) and (ball.ycor() < pad_left.ycor() + 28 and ball.ycor() > pad_left.ycor() - 40 ):
        ball.setx(-340)
        ball.dx *= -1
