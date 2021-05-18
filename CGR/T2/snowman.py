from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
from colors import *
from shapes import SolidCylinder

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

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glClearColor(*blue_sky)
    glLoadIdentity()

    gluLookAt(4.2, 1.4, 0.0, 0.0, 0.4, 0.0, 0.0, 1.0, 0.0)

    # Controle de camera
    if spin:
        angle_h += turn_h * 0.5
        angle_v += turn_v
    angle_h %= 360
    angle_v %= 360

    # Angulo do objeto
    glRotatef(angle_h, 0, 1, 0)
    glRotatef(angle_v, 1, 0, 1)

    glPushMatrix()
    # Ajustando para centro do frame
    glTranslatef(0.0, 0.2, 0.0)

    # Base
    glPushMatrix()
    glTranslatef(0.0, -0.298, 0.0)
    glRotatef(90, 1, 0, 0)
    glColor3f(*grass)
    glutSolidCylinder(1.13, 0.002, 100, 1)
    glPopMatrix()

    # Cor da neve
    glColor3f(*white)
    # Bola maior

    glTranslatef(0.0, 0.0, 0.0)
    glutSolidSphere(0.45, render_quality, render_quality * 2)

    # Bola meio
    glTranslatef(0.0, 0.45, 0.0)
    glutSolidSphere(0.3, render_quality, render_quality * 2)

    # Bola cabeca
    glTranslatef(0.0, 0.35, 0.0)
    glutSolidSphere(0.25, render_quality, render_quality * 2)

    # Olho Direito
    glPushMatrix()
    glRotatef(26.0, 0, 1, 0)
    glTranslatef(0.21, 0.08, 0.0)
    glColor3f(0.1, 0.1, 0.1)
    glutSolidSphere(0.04, 8, 8)
    glPopMatrix()

    # Olho Esquerdo
    glPushMatrix()
    glRotatef(-26.0, 0, 1, 0)
    glTranslatef(0.21, 0.08, 0.0)
    glutSolidSphere(0.04, 8, 8)
    glPopMatrix()

    # Nariz
    glPushMatrix()
    glTranslatef(0.22, -0.01, 0.0)
    glRotatef(90, 0, 1, 0)
    glColor3f(*red)
    glutSolidCone(0.03, 0.18, 8, 6)
    glPopMatrix()

    # Chapeuzinho
    glColor3f(*black)
    glPushMatrix()
    glTranslatef(0, 0.25, 0)
    SolidCylinder(0.2, 0.03, render_quality)
    glColor3f(*red)
    glTranslatef(0, 0.08, 0)
    SolidCylinder(0.11, 0.05, render_quality)
    glColor3f(*dark_gray)
    SolidCylinder(0.1, 0.3, render_quality)
    glPopMatrix()

    # Base do globo de vidro
    glEnable(GL_BLEND)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
    glPushMatrix()
    glTranslatef(0.0, -1.1, 0.0)
    glColor3f(*dark_gray)
    glRotatef(90, 1, 0, 0)
    glutSolidCylinder(1.23, 0.4, 100, 1)
    glPopMatrix()
    glPushMatrix()
    glTranslatef(0.0, -1.13, 0.0)
    glColor3f(*light_gray)
    glPushMatrix()
    glRotatef(90, 1, 0, 0)
    glutSolidCylinder(1.3, 0.4, 100, 1)
    glPopMatrix()
    glTranslatef(0.0, -0.08, 0.0)
    glColor3f(*dark_gray)
    glPushMatrix()
    glRotatef(90, 1, 0, 0)
    glutSolidCylinder(1.308, 0.24, 100, 1)
    glPopMatrix()
    glPopMatrix()

    # Globo de vidro
    # Interno
    glPushMatrix()
    glColor4f(0.8, 0.8, 0.8, 0.05)
    glTranslatef(0.0, -0.5, 0.0)
    glRotatef(90.0, 1, 0, 0)
    glutSolidSphere(1.3, render_quality, render_quality)
    glPopMatrix()
    # Externo
    glPushMatrix()
    glColor4f(0.8, 0.8, 0.8, 0.1)
    glTranslatef(0.0, -0.5, 0.0)
    glRotatef(90.0, 1, 0, 0)
    glutSolidSphere(1.4, render_quality, render_quality)
    glPopMatrix()

    glDisable(GL_BLEND)
    glPopMatrix()
    glFlush()
    glutSwapBuffers()


width = 800
height = 600
glutInit()
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH)
glutInitWindowSize(width, height)
glutCreateWindow("Boneco de Neve - Menderson e Vinicius")

glutDisplayFunc(display)
glutIdleFunc(display)
glutKeyboardFunc(keyboard)

glMatrixMode(GL_PROJECTION)
glViewport(0, 0, width, height)
glMatrixMode(GL_PROJECTION)
glLoadIdentity()
aspect = width / height
gluPerspective(45, aspect, 0.01, 100.0)
glMatrixMode(GL_MODELVIEW)
glShadeModel(GL_SMOOTH)
glClearDepth(1.0)
glEnable(GL_DEPTH_TEST)
glDepthFunc(GL_LEQUAL)
glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST)
glClearColor(0.0, 0.0, 0.0, 1.0)

# Controle de textura
mat_shininess = [15.0]
mat_specular = [0.75, 0.75, 0.75, 0.75]

# Controle de luz
light_ambient = [0.6, 0.6, 0.6, 1.0]
light_diffuse = [0.8, 0.8, 0.8, 0.8]
light_specular = [1.0, 1.0, 1.0, 0.3]
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
