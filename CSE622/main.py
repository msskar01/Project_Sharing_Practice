# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.

import numpy as np
import matplotlib.pyplot as plt


class Ship:
    def __init__(self, xcord, ycord, zcord, xvelocity, yvelocity, zvelocity, xacceleration, yacceleration,
                 zacceleration, maxvelocity):
        self.xcord = xcord
        self.ycord = ycord
        self.zcord = zcord
        self.xvelocity = xvelocity
        self.yvelocity = yvelocity
        self.zvelocity = zvelocity
        self.xacceleration = xacceleration
        self.yacceleration = yacceleration
        self.zacceleration = zacceleration
        self.maxvelocity = maxvelocity

    def update(self):
        self.xvelocity += self.xacceleration
        self.yvelocity += self.yacceleration
        self.zvelocity += self.zacceleration
        if self.xvelocity < -self.maxvelocity:
            self.xvelocity = -self.maxvelocity
        elif self.xvelocity > self.maxvelocity :
            self.xvelocity = self.maxvelocity
        if self.yvelocity < -self.maxvelocity :
            self.yvelocity = -self.maxvelocity
        elif self.yvelocity > self.maxvelocity :
            self.yvelocity = self.maxvelocity
        if self.zvelocity < -self.maxvelocity :
            self.zvelocity = -self.maxvelocity
        elif self.zvelocity > self.maxvelocity :
            self.zvelocity = self.maxvelocity
        self.xcord += self.xvelocity
        self.ycord += self.yvelocity
        self.zcord += self.zvelocity

    def update_acceleration(self, xacceleration, yacceleration, zacceleration):
        self.xacceleration = xacceleration
        self.yacceleration = yacceleration
        self.zacceleration = zacceleration


class Goal:
    def __init__(self, xcord, ycord, zcord):
        self.xcord = xcord
        self.ycord = ycord
        self.zcord = zcord


def calculate_distance(object1, object2):
    return np.sqrt(float((object2.xcord - object1.xcord) ** 2) + float((object2.ycord - object1.ycord) ** 2) + float(
        (object2.zcord - object1.zcord) ** 2))


def calculate_theta(obect1, object2):
    dotprod = obect1.xcord * object2.xcord + obect1.ycord * object2.ycord + obect1.zcord * object2.zcord
    distance = np.sqrt(obect1.xcord ** 2 + obect1.ycord ** 2 + obect1.zcord ** 2) * np.sqrt(
        object2.xcord ** 2 + object2.ycord ** 2 + object2.zcord ** 2)
    theta = np.arccos(dotprod / round(distance, 4))
    return theta


def ship1_max_acceleration(acceleration):
    if acceleration > 5:
        acceleration = 5
    elif acceleration < -5:
        acceleration = -5
    return acceleration


def ship2_max_acceleration(acceleration):
    if acceleration > 15:
        acceleration = 15
    elif acceleration < -15:
        acceleration = -15
    return acceleration


ship1 = Ship(100, 100, 100, 10, 10, -10, 0, 0, 0, 15)
ship2 = Ship(120, 100, 100, -10, -10, 10, 0, 0, 0, 30)
goal = Goal(5, 5, 5)
time = 0

ship1_path = [[], [], []]
ship2_path = [[], [], []]

while True:
    ship1_path[0].append(ship1.xcord)
    ship1_path[1].append(ship1.ycord)
    ship1_path[2].append(ship1.zcord)
    ship2_path[0].append(ship2.xcord)
    ship2_path[1].append(ship2.ycord)
    ship2_path[2].append(ship2.zcord)

    theta = calculate_theta(ship1, goal)
    distance = calculate_distance(ship1, ship2)
    if ship1.xcord == goal.xcord and ship1.ycord == goal.ycord and ship1.zcord == goal.zcord:
        break
    elif distance < 10:
        break

    vector_to_goal = [goal.xcord - ship1.xcord,
                      goal.ycord - ship1.ycord,
                      goal.zcord - ship1.zcord]
    vector_velocity = [(ship1.xcord + ship1.xvelocity) - ship1.xcord,
                       (ship1.ycord + ship1.yvelocity) - ship1.ycord,
                       (ship1.zcord + ship1.zvelocity) - ship1.zcord]
    ship1_acceleration = [vector_to_goal[0] + vector_velocity[0],
                          vector_to_goal[1] + vector_velocity[1],
                          vector_to_goal[2] + vector_velocity[2]]

    ship1_acceleration[0] = ship1_max_acceleration(ship1_acceleration[0])
    ship1_acceleration[1] = ship1_max_acceleration(ship1_acceleration[1])
    ship1_acceleration[2] = ship1_max_acceleration(ship1_acceleration[2])

    # checks if we will go through the goal with ship1 with current speed and slows down so that we get exactly to the
    # goal instead of speeding through it
    if ship1.xcord <= goal.xcord <= ship1.xcord + ship1.xvelocity + ship1_acceleration[0] or\
            ship1.xcord + ship1.xvelocity + ship1_acceleration[0] <= goal.xcord <= ship1.xcord:
        ship1.xvelocity = goal.xcord - ship1.xcord
        ship1_acceleration[0] = 0
    if ship1.ycord <= goal.ycord <= ship1.ycord + ship1.yvelocity + ship1_acceleration[1] or\
            ship1.ycord + ship1.yvelocity + ship1_acceleration[1] <= goal.ycord <= ship1.ycord:
        ship1.yvelocity = goal.ycord - ship1.ycord
        ship1_acceleration[1] = 0
    if ship1.zcord <= goal.zcord <= ship1.zcord + ship1.zvelocity + ship1_acceleration[2] or\
            ship1.zcord + ship1.zvelocity + ship1_acceleration[2] <= goal.zcord <= ship1.zcord:
        ship1.zvelocity = goal.zcord - ship1.zcord
        ship1_acceleration[2] = 0

    # find the acceleration of ship2 to ship1
    vector_to_ship1 = [ship1.xcord + ship1.xacceleration - ship2.xcord,
                       ship1.ycord + ship1.yacceleration - ship2.ycord,
                       ship1.zcord + ship1.zacceleration - ship2.zcord]
    vector_velocity = [(ship2.xcord + ship2.xvelocity) - ship2.xcord,
                       (ship2.ycord + ship2.yvelocity) - ship2.ycord,
                       (ship2.zcord + ship2.zvelocity) - ship2.zcord]
    ship2_acceleration = [vector_to_ship1[0] * 2,
                          vector_to_ship1[1] * 2,
                          vector_to_ship1[2] * 2]

    ship2_acceleration[0] = ship2_max_acceleration(ship2_acceleration[0])
    ship2_acceleration[1] = ship2_max_acceleration(ship2_acceleration[1])
    ship2_acceleration[2] = ship2_max_acceleration(ship2_acceleration[2])

    # checks if we are going too fast toward ship1 and slows down, so we don't speed past if we are
    if np.abs(ship2.xvelocity + ship2.xcord) > np.abs(ship1.xcord):
        ship2_acceleration[0] = (ship1.xcord + ship1.xvelocity) - (ship2.xvelocity + ship2.xcord)
        ship2_acceleration[0] = ship2_max_acceleration(ship2_acceleration[0])
    if np.abs(ship2.yvelocity + ship2.ycord) > np.abs(ship1.ycord):
        ship2_acceleration[1] = (ship1.ycord + ship1.yvelocity) - (ship2.yvelocity + ship2.ycord)
        ship2_acceleration[1] = ship2_max_acceleration(ship2_acceleration[1])
    if np.abs(ship2.zvelocity + ship2.zcord) > np.abs(ship1.zcord):
        ship2_acceleration[2] = (ship1.zcord + ship1.zvelocity) - (ship2.zvelocity + ship2.zcord)
        ship2_acceleration[2] = ship2_max_acceleration(ship2_acceleration[2])

    ship1.update_acceleration(ship1_acceleration[0],
                              ship1_acceleration[1],
                              ship1_acceleration[2])
    ship1.update()

    ship2.update_acceleration(ship2_acceleration[0],
                              ship2_acceleration[1],
                              ship2_acceleration[2])
    ship2.update()

    time += 1

print(time)
print(ship1_path)
print(ship2_path)

ax = plt.axes(projection='3d')

x = ship1_path[0]
y = ship1_path[1]
z = ship1_path[2]

ax.plot3D(x, y, z, color="blue")

x = ship2_path[0]
y = ship2_path[1]
z = ship2_path[2]

ax.plot3D(x, y, z, color="red")

ax.scatter(goal.xcord, goal.ycord, goal.zcord)

plt.show()
