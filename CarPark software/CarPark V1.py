carpark_1 = ["enfield", "walthamstow", "greenpark", "romford", "tooting"]
carpark_2 = ["wimbledon", "westminister", "chingford", "bradford", "hornchurch"]

def calculate_cost(a,b,c):
  cost=a*b
  stay_price=cost + c
  return round(stay_price, 2)


print("Welcome to Thash's Car Park")
hrs = int(input("How many hours did you stay? "))
vehicle = input("is your vehicle electric (y/n)").lower().strip()
if vehicle == "y":
  vehicle = 0.8
else:
  vehicle = 1.2

carpark = input("which carpark did you stay at? ").lower().strip()
if carpark in carpark_1:
  carpark = 1
elif carpark in carpark_2:
  carpark = 2.5
else:
  print("ERROR CAR PARK NOT FOUND")

print("Please Pay: £", calculate_cost(hrs,vehicle,carpark))


  
