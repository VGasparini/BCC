from random import randint as rand
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
from colors import *

QTDFLOCOS = 1000
Floco = []

class Flake:
    def __init__(self):
        self.viva = True
        self.vida = 2
        self.desaparecer = rand(1,99) * 0.001
        self.xPos = rand(-20,20)
        self.yPos = rand(-20,20)
        self.zPos = rand(1,20)
        self.vel = -rand(1,2)/30
        self.gravidade = -0.00015

def init():
    global Floco
    Floco = [Flake() for i in range(QTDFLOCOS)]

def snowRain():
    global Floco
    for loop in range(0,QTDFLOCOS,2):
        if (Floco[loop].viva):
            x = Floco[loop].xPos
            y = Floco[loop].yPos
            z = Floco[loop].zPos - 25
            glBegin(GL_LINES)
            glVertex3f(x , y, z)       # faz as linhas ficarem em 90º com o x-1
            glVertex3f(x, y + 0.1, z)  # Tamanho do Floco é o 1
            glEnd()
            Floco[loop].yPos += Floco[loop].vel
            Floco[loop].vel += Floco[loop].gravidade
            Floco[loop].vida -= Floco[loop].desaparecer
            if (Floco[loop].vida < 0.0):
                Floco[loop] = Flake()

def drawScene():
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
	glMatrixMode(GL_MODELVIEW)
	# glLoadIdentity()
	# glRotatef(0.0, 0.0, 1.0, 0.0)
	# glRotatef(0.0, 1.0, 0.0, 0.0)
	# glEnd()
	snowRain()
	glutSwapBuffers()


def reshape(w, h):
	glViewport(0, 0, w, h)
	glMatrixMode(GL_PROJECTION)
	glLoadIdentity()
	gluPerspective(55, w / h, .1, 200)
	glMatrixMode(GL_MODELVIEW)
	glLoadIdentity()

def idle():
	glutPostRedisplay()

glutInit()
glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE)
glutInitWindowSize(640, 480)    #tamanho da tela
glutCreateWindow("Neve - Vinicius e Menderson")
init()                          #inicia o glut
glutDisplayFunc(drawScene)      #callback, qual função vai ser chamada para mostrar
glutReshapeFunc(reshape)
glutIdleFunc(idle)
glutMainLoop()

