from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
from colors import *
from math import pi, sin, cos
from shapes import (
    SolidRectangle,
    SolidCylinder,
    SolidPrismaTriangular,
    DrawTower,
    DrawWall,
)

scale = 8.0
angle_h = 300.0
angle_v = 0
spin = True
turn_h = 1
turn_v = 0
render_quality = 100  # max = 100


def keyboard(key, x, y):
    global spin, turn_h, turn_v, angle_h, angle_v, render_quality

    key = ord(key)
    # Esc para sair
    if key == 27:
        exit(0)
    elif key == ord("s"):
        spin = not spin
    elif key == ord("a"):
        turn_h = -1
    elif key == ord("d"):
        turn_h = 1
    elif key == ord("w"):
        turn_v = 0.5
    elif key == ord("x"):
        turn_v = -0.5

    # Controle de render
    elif key == ord("+"):
        render_quality += 5
    elif key == ord("-"):
        render_quality -= 2

    else:
        angle_h = 300.0
        angle_v = 0
        turn_h = 1
        turn_v = 0
        render_quality = 100


def display():

    global spin, angle_h, angle_v

    glMatrixMode(GL_MODELVIEW)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glClearColor(*blue_sky)
    glLoadIdentity()

    gluLookAt(20.0, 10.0, 20.0, 0.0, 2.0, 0.0, 0.0, 1.0, 0.0)

    # Controle de camera
    if spin:
        angle_h += turn_h * 0.5
        angle_v += turn_v
    angle_h %= 360
    angle_v %= 360

    # Angulo do objeto
    glRotatef(angle_h, 0, 1, 0)
    glRotatef(angle_v, 1, 0, 1)

    # Base
    glPushMatrix()
    glColor3f(*grass)
    glBegin(GL_QUADS)
    glNormal3f(0.0, 1.0, 0.0)
    glVertex3f(-30.0, 0.0, -30.0)
    glVertex3f(-30.0, 0.0, 30.0)
    glVertex3f(30.0, 0.0, 30.0)
    glVertex3f(30.0, 0.0, -30.0)
    glEnd()

    # Chão do castelo
    glColor3f(0.3, 0.3, 0.2)
    glBegin(GL_QUADS)
    glNormal3f(0.0, 1.0, 0.0)
    glVertex3f(-scale, 0.01, -scale)
    glVertex3f(-scale, 0.01, scale)
    glVertex3f(scale, 0.01, scale)
    glVertex3f(scale, 0.01, -scale)
    glEnd()

    # Torre central
    glPushMatrix()
    glColor3f(*silver)
    glTranslatef(0.0, 3.25, 0.0)
    glPushMatrix()
    glScaled(3.7, 10, 3.7)
    glutSolidCube(1.0)
    glPopMatrix()
    glColor3f(*red)
    glTranslatef(0.0, 6.5, 0.0)
    SolidPrismaTriangular(4, 3, 4)
    glPopMatrix()

    # Torre 1-2
    glPushMatrix()
    glColor3f(*white)
    glTranslatef(8, 0, -2)
    glPushMatrix()
    glScaled(2.1, 8.5, 2.4)
    glutSolidCube(1.0)
    glPopMatrix()
    glColor3f(*red)
    glTranslatef(0.0, 5.1, 0.0)
    SolidPrismaTriangular(3, 2, 4.5)
    glPopMatrix()
    glPushMatrix()
    glColor3f(*white)
    glTranslatef(8, 0, 2)
    glPushMatrix()
    glScaled(2.1, 8.5, 2.4)
    glutSolidCube(1.0)
    glPopMatrix()
    glColor3f(*red)
    glTranslatef(0.0, 5.1, 0.0)
    SolidPrismaTriangular(3, 2, 4.5)
    glPopMatrix()

    # Torre 1
    DrawTower(light_gray, black, scale, scale)

    # Parede 1-2
    DrawWall(dark_gray, scale, scale / 2, 1, scale - 2)
    DrawWall(dark_gray, scale, -scale / 2, 1, scale - 2)

    # Torre 2
    DrawTower(light_gray, black, scale, -scale)

    # Parede 2-3
    DrawWall(dark_gray, 0, -scale, 2 * scale, 1)

    # Torre 3
    DrawTower(light_gray, black, -scale, -scale)

    # Parede 3-4
    DrawWall(dark_gray, -scale, 0, 1, 2 * scale)

    # Torre 4
    DrawTower(light_gray, black, -scale, scale)

    # Parede 4-1
    DrawWall(dark_gray, 0, scale, 2 * scale, 1)

    glEnable(GL_BLEND)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
    glDisable(GL_BLEND)
    glPopMatrix()

    glFlush()
    glutSwapBuffers()


width = 800
height = 600
glutInit()
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH)
glutInitWindowSize(width, height)
glutCreateWindow("Castelo - Menderson e Vinicius")

glutDisplayFunc(display)
glutIdleFunc(display)
glutKeyboardFunc(keyboard)

glViewport(0, 0, width, height)
glLoadIdentity()
glMatrixMode(GL_PROJECTION)
aspect = width / height
gluPerspective(45, aspect, 0.01, 100.0)
glMatrixMode(GL_MODELVIEW)
glShadeModel(GL_SMOOTH)
glClearDepth(1.0)
glEnable(GL_DEPTH_TEST)
glDepthFunc(GL_LEQUAL)
glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST)
glClearColor(0.0, 0.0, 0.0, 1.0)

mat_shininess = [8.0]
mat_specular = [0.75, 0.75, 0.75, 0.75]

light_ambient = [0.4, 0.4, 0.4, 1.0]
light_diffuse = [0.8, 0.8, 0.8, 0.9]
light_specular = [1.0, 1.0, 1.0, 0.1]
light_position = [6.0, 6.0, 2.0, 0.0]

glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular)
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess)

glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient)
glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse)
glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular)

glLightfv(GL_LIGHT0, GL_POSITION, light_position)

glEnable(GL_LIGHTING)
glEnable(GL_LIGHT0)

glEnable(GL_COLOR_MATERIAL)

glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE)

glutMainLoop()
