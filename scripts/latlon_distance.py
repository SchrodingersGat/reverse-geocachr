from math import *

def distance(p1, p2):
    lat1,lon1 = p1
    lat2,lon2 = p2

    lat1 = lat1 * pi / 180
    lat2 = lat2 * pi / 180
    lon1 = lon1 * pi / 180
    lon2 = lon2 * pi / 180

    R = 6371.0

    dLat = (lat2 - lat1)
    dLon = (lon2 - lon1)


    a1 = pow(sin(dLat/2),2)

    a2 = pow(sin(dLon/2),2)
    a3 = cos(lat1) * cos(lat2)


    a = a1 + a2*a3
    
    c = 2 * atan2(sqrt(a),sqrt(1-a))

    d = R * c

    return d

#stedman house
LAT1 =-41.540351
LON1 = 146.411132

#walters house 
LAT2 = -43.033823
LON2 = 147.270602

P1 = (LAT1,LON1)
P2 = (LAT2,LON2)

print "Expected Distance:"
print "179.97Km"
print ""

print "Distance:"
print distance(P2,P1)
