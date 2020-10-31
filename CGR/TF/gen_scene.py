from random import randint as r

head = '''set zoom 0.88
set scale 2
set scatter 5
set campos 0 0 -70.00
add light 22 6 2 0.78 0.78 0.78
add light 19 9 27 0.96 0.96 0.96
add light 21 -23 -1 0.72 0.72 0.72
add light 29  29  29 1.00 1.00 1.00
add sphere -13 0 -10 8 1
set sphere 0 color 1 0 1
set sphere 0 shiny 1
add sphere -1 15 -32 7.5 0
set sphere 1 color 2.55 2.15 0 
set sphere 1 shiny .3
set plane 3 shiny 0.8
set plane 3 rough 0.02
set shadowres 50'''
print(head)
frames = int(input())

x_c = 0
y_c = 0
z_c = 0
x_cam = 0.65
y_cam = 0.4
z_cam = 0.05
x_cam_i = x_cam/frames
y_cam_i = y_cam/frames
z_cam_i = z_cam/frames

x_p = 0
y_p = 0
z_p = -70
x_pos = 20
y_pos = -20
z_pos = -70
x_pos_i = x_pos/frames
y_pos_i = y_pos/frames
z_pos_i = 0

for i in range(frames):
    print("set camangle %.2f %.2f %.2f" % (x_c,y_c,z_c))
    print("set campos %.2f %.2f %.2f" % (x_p, y_p, z_p))
    print("render")
    print("export frame_%s.png" % (str(i).zfill(3)))
    x_c += x_cam_i
    y_c += y_cam_i
    z_c += z_cam_i
    x_p += x_pos_i
    y_p += y_pos_i
    z_p += z_pos_i

x_cam = -0.2
y_cam = -0.2
z_cam = 0.05
x_cam_i = (x_c-x_cam)/frames
y_cam_i = (y_c-y_cam)/frames
z_cam_i = (z_c-z_cam)/frames

x_pos = -20
y_pos = 20
z_pos = -70
x_pos_i = (x_p - x_pos)/frames
y_pos_i = (y_p - y_pos)/frames
z_pos_i = 0

lista = list()

for i in range(50,frames+50):
    a = "set camangle {:.2f} {:.2f} {:.2f}".format(x_c,y_c,z_c)
    print(a)
    b = "set campos {:.2f} {:.2f} {:.2f}".format(x_p, y_p, z_p)
    print(b)
    print("render")
    c = "export frame_{}.png".format(str(i).zfill(3))
    print(c)
    x_c -= x_cam_i
    y_c -= y_cam_i
    z_c -= z_cam_i
    x_p -= x_pos_i
    y_p -= y_pos_i
    z_p -= z_pos_i
    lista.append(a+"\n"+b+"\nrender\n"+c)

lista = lista[::-1]

#for i in lista:
#    print(i)
print("exit")