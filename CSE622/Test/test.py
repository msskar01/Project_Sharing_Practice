import numpy as np
import random
import operator


class Elevator:
    def __init__(self, capacity, floors, current_floor, time, is_moving, people_on, door_opens):
        self.capacity = capacity
        self.floors = floors
        self.current_floor = current_floor
        self.time = time
        self.is_moving = is_moving
        self.people_on = people_on
        self.door_opens = door_opens
        self.door_closes = 0
        self.target_floor = 'G'
        self.target_arrival = 800


class Person:
    def __init__(self, going_floor, show_up, leave):
        self.going_floor = going_floor
        self.show_up = show_up
        self.leave = leave


elevator = Elevator(12, ['G', 2, 3, 4], 'G', 800, False, [], 800)

people = []
takenstairs2 = []
takenstairs3 = []
takenstairs4 = []
timespentwaiting = []
averagetimewaiting = []
peoplewaiting = []
percent2 = []
percent3 = []
percent4 = []
percent = []
inline815 = 0
inline830 = 0
inline845 = 0
inline860 = 0
for time in np.arange(800, 860, 0.25):
    if time.is_integer():
        for n in range(6):
            people.append(Person(random.randrange(2, 5), time, 0))
            if len(people) > 12:
                if people[-1].going_floor == 2 and random.randrange(2) == 1:
                    takenstairs2.append(people.pop(-1))
                elif people[-1].going_floor == 3 and random.randrange(3) == 2:
                    takenstairs3.append(people.pop(-1))
                elif people[-1].going_floor == 4 and random.randrange(10) == 9:
                    takenstairs4.append(people.pop(-1))
        percent2.append(len(takenstairs2) / (len(people) + len(averagetimewaiting)))
        percent3.append(len(takenstairs3) / (len(people) + len(averagetimewaiting)))
        percent4.append(len(takenstairs4) / (len(people) + len(averagetimewaiting)))
        percent.append((len(takenstairs2) + len(takenstairs3) + len(takenstairs4)) / (len(people) + len(averagetimewaiting)))
    elevator.time = time

    if elevator.door_closes == time:
        elevator.is_moving = True
    if elevator.current_floor == 'G' and elevator.is_moving == False:
        while len(people) != 0 and len(elevator.people_on) < elevator.capacity:
            people[0].leave = time
            timespentwaiting.append(people[0].leave - people[0].show_up)
            elevator.people_on.append(people.pop(0))

    if elevator.is_moving == True and elevator.door_closes == time:
        elevator.people_on.sort(key=operator.attrgetter('going_floor'))
        if len(elevator.people_on) == 0:
            elevator.target_floor = 'G'
        for person in elevator.people_on:
            if elevator.target_floor == elevator.current_floor:
                elevator.target_floor = person.going_floor
            if elevator.target_floor > person.going_floor:
                elevator.target_floor = person.going_floor
        if elevator.target_arrival < time:
            if (elevator.target_floor == 2 and elevator.current_floor == 'G') or (elevator.target_floor == 'G' and elevator.current_floor == 2):
                elevator.target_arrival = time + 1
            elif (elevator.target_floor == 3 and elevator.current_floor == 'G') or (elevator.target_floor == 'G' and elevator.current_floor == 3):
                elevator.target_arrival = time + 1.5
            elif (elevator.target_floor == 4 and elevator.current_floor == 'G') or (elevator.target_floor == 'G' and elevator.current_floor == 4):
                elevator.target_arrival = time + 1.75
            elif (elevator.target_floor == 3 and elevator.current_floor == 2) or (elevator.target_floor == 2 and elevator.current_floor == 3):
                elevator.target_arrival = time + 0.5
            elif elevator.target_floor == 4 and elevator.current_floor == 2:
                elevator.target_arrival = time + 0.5
            elif elevator.target_floor == 4 and elevator.current_floor == 3:
                elevator.target_arrival = time + 0.25

    if elevator.target_arrival == time:
        elevator.is_moving = False
        elevator.door_opens = time
        elevator.current_floor = elevator.target_floor
        for person in list(elevator.people_on):
            if person.going_floor == elevator.target_floor:
                elevator.people_on.remove(person)

    if elevator.door_opens == time and elevator.is_moving == False:
        elevator.door_closes = elevator.door_opens + 0.5

    if time == 815:
        inline815 = len(people)
    elif time == 830:
        inline830 = len(people)
    elif time == 845:
        inline845 = len(people)

    add = 0
    for person in people:
        add += time - person.show_up
    averagetimewaiting.append((add+sum(timespentwaiting))/(len(people)+len(timespentwaiting)))
    if time.is_integer():
        peoplewaiting.append(len(people))


while len(people) != 0:
    elevator.time += 0.25
    if elevator.time == 860:
        inline860 = len(people)

    if elevator.door_closes == elevator.time:
        elevator.is_moving = True
    if elevator.current_floor == 'G' and elevator.is_moving == False:
        while len(people) != 0 and len(elevator.people_on) < elevator.capacity:
            people[0].leave = elevator.time
            timespentwaiting.append(people[0].leave - people[0].show_up)
            elevator.people_on.append(people.pop(0))

    if elevator.is_moving == True and elevator.door_closes == elevator.time:
        elevator.people_on.sort(key=operator.attrgetter('going_floor'))
        if len(elevator.people_on) == 0:
            elevator.target_floor = 'G'
        for person in elevator.people_on:
            if elevator.target_floor == elevator.current_floor:
                elevator.target_floor = person.going_floor
            if elevator.target_floor > person.going_floor:
                elevator.target_floor = person.going_floor
        if elevator.target_arrival < elevator.time:
            if (elevator.target_floor == 2 and elevator.current_floor == 'G') or (elevator.target_floor == 'G' and elevator.current_floor == 2):
                elevator.target_arrival = elevator.time + 1
            elif (elevator.target_floor == 3 and elevator.current_floor == 'G') or (elevator.target_floor == 'G' and elevator.current_floor == 3):
                elevator.target_arrival = elevator.time + 1.5
            elif (elevator.target_floor == 4 and elevator.current_floor == 'G') or (elevator.target_floor == 'G' and elevator.current_floor == 4):
                elevator.target_arrival = elevator.time + 1.75
            elif (elevator.target_floor == 3 and elevator.current_floor == 2) or (elevator.target_floor == 2 and elevator.current_floor == 3):
                elevator.target_arrival = elevator.time + 0.5
            elif elevator.target_floor == 4 and elevator.current_floor == 2:
                elevator.target_arrival = elevator.time + 0.5
            elif elevator.target_floor == 4 and elevator.current_floor == 3:
                elevator.target_arrival = elevator.time + 0.25

    if elevator.target_arrival == elevator.time:
        elevator.is_moving = False
        elevator.door_opens = elevator.time
        elevator.current_floor = elevator.target_floor
        for person in list(elevator.people_on):
            if person.going_floor == elevator.target_floor:
                elevator.people_on.remove(person)

    if elevator.door_opens == elevator.time and elevator.is_moving == False:
        elevator.door_closes = elevator.door_opens + 0.5

    add = 0
    for person in people:
        add += elevator.time - person.show_up
    averagetimewaiting.append((add+sum(timespentwaiting))/(len(people)+len(timespentwaiting)))
    if elevator.time.is_integer():
        peoplewaiting.append(len(people))

print(timespentwaiting)
print(sum(timespentwaiting)/len(timespentwaiting))
print(len(takenstairs2))
print(len(takenstairs3))
print(len(takenstairs4))
print(percent2[-1])
print(percent3[-1])
print(percent4[-1])
print(percent[-1])
print(elevator.time - 800)
print(inline815)
print(inline830)
print(inline845)
print(inline860)

from matplotlib import pyplot as plt

plt.plot(np.arange(0, elevator.time - 800 + 0.25, 0.25), averagetimewaiting)
plt.xlabel('minutes')
plt.ylabel('average time spent waiting')
plt.show()

plt.plot(np.arange(0, elevator.time - 800), peoplewaiting)
plt.xlabel('minutes')
plt.ylabel('number of people waiting at elevator')
plt.show()

plt.plot(percent, color='black')
plt.plot(percent2, color='r')
plt.plot(percent3, color='b')
plt.plot(percent4, color='g')
plt.show()

