from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
from math import pi as M_PI
from math import sin, cos


def ObtainQuadFaceNormal(v1, v2, v3, v4):
    n = [0, 0, 0]
    l = 0.0
    for i in range(3):
        n[i] = (v1[i] + v2[i] + v3[i] + v4[i]) / 4
    l = (n[0] * n[0] + n[1] * n[1] + n[2] * n[2]) ** (1 / 2)
    for i in range(3):
        n[i] /= -l
    return n


def ObtainTriangleFaceNormal(v1, v2, v3):
    n = [0, 0, 0]
    l = 0.0
    for i in range(3):
        n[i] = (v1[i] + v2[i] + v3[i]) / 3
    l = (n[0] * n[0] + n[1] * n[1] + n[2] * n[2]) ** (1 / 2)
    for i in range(3):
        n[i] /= -l
    return n


def SolidRectangle(m, h, n):

    m /= 2
    h /= 2
    n /= 2

    normal = [0, 0, 0]

    v = [
        [-m, -h, -n],
        [-m, h, -n],
        [m, h, -n],
        [m, -h, -n],
        [-m, -h, n],
        [-m, h, n],
        [m, h, n],
        [m, -h, n],
    ]

    # Base
    glNormal3f(0.0, -1.0, 0.0)
    glBegin(GL_QUADS)
    glVertex3fv(v[0])
    glVertex3fv(v[3])
    glVertex3fv(v[7])
    glVertex3fv(v[4])
    glEnd()

    # Frente
    glNormal3f(0.0, 0.0, 1.0)
    glBegin(GL_QUADS)
    glVertex3fv(v[0])
    glVertex3fv(v[3])
    glVertex3fv(v[2])
    glVertex3fv(v[1])
    glEnd()

    # Direita
    glNormal3f(1.0, 0.0, 0.0)
    glBegin(GL_QUADS)
    glVertex3fv(v[3])
    glVertex3fv(v[7])
    glVertex3fv(v[6])
    glVertex3fv(v[2])
    glEnd()

    # Esquerda
    glNormal3f(-1.0, 0.0, 0.0)
    glBegin(GL_QUADS)
    glVertex3fv(v[0])
    glVertex3fv(v[1])
    glVertex3fv(v[5])
    glVertex3fv(v[4])
    glEnd()

    # Trás
    glNormal3f(0.0, 0.0, -1.0)
    glBegin(GL_QUADS)
    glVertex3fv(v[4])
    glVertex3fv(v[7])
    glVertex3fv(v[6])
    glVertex3fv(v[5])
    glEnd()

    # Topo
    glNormal3f(0.0, 1.0, 0.0)
    glBegin(GL_QUADS)
    glVertex3fv(v[1])
    glVertex3fv(v[2])
    glVertex3fv(v[6])
    glVertex3fv(v[5])
    glEnd()


def SolidCylinder(radius, height, sides):
    height /= 2
    normal = [0, 0, 0]

    # Base
    glBegin(GL_TRIANGLE_FAN)
    normal[0] = 0.0
    normal[1] = -height
    normal[2] = 0.0
    glNormal3f(0.0, 0.0, 0.0)
    glVertex3f(0.0, -height, 0.0)
    for i in range(sides + 1):
        x = cos((2.0 * M_PI * i) / sides) * radius
        z = sin((2.0 * M_PI * i) / sides) * radius
        normal[0] = x
        normal[1] = height
        normal[2] = z
        glNormal3fv(normal)
        glVertex3f(x, -height, z)
    glEnd()

    # Topo
    glBegin(GL_TRIANGLE_FAN)
    glVertex3f(0.0, height, 0.0)
    for i in range(sides + 1):
        x = cos((2.0 * M_PI * i) / sides) * radius
        z = sin((2.0 * M_PI * i) / sides) * radius
        normal[0] = x
        normal[1] = height
        normal[2] = z
        glNormal3fv(normal)
        glVertex3f(x, height, z)
    glEnd()

    # Corpo
    glBegin(GL_QUAD_STRIP)
    for i in range(sides + 1):
        x = cos((2.0 * M_PI * i) / sides) * radius
        z = sin((2.0 * M_PI * i) / sides) * radius
        normal[0] = x
        normal[1] = 0.0
        normal[2] = z
        glNormal3fv(normal)
        glVertex3f(x, -height, z)
        glNormal3fv(normal)
        glVertex3f(x, height, z)
    glEnd()


def SolidPrismaTriangular(m, h, n):

    m /= 2
    h /= 2
    n /= 2

    normal = [0, 0, 0]

    v = [[-m, -h, -n], [0, h, -n], [m, -h, -n], [-m, -h, n], [0, h, n], [m, -h, n]]

    # Face direita
    normal = ObtainQuadFaceNormal(v[1], v[2], v[5], v[4])
    glNormal3fv(normal)
    glBegin(GL_QUADS)
    glVertex3fv(v[1])
    glVertex3fv(v[2])
    glVertex3fv(v[5])
    glVertex3fv(v[4])
    glEnd()

    # Face esquerda
    normal = ObtainQuadFaceNormal(v[0], v[1], v[4], v[3])
    glNormal3fv(normal)
    glBegin(GL_QUADS)
    glVertex3fv(v[0])
    glVertex3fv(v[1])
    glVertex3fv(v[4])
    glVertex3fv(v[3])
    glEnd()

    # Base
    normal = ObtainQuadFaceNormal(v[0], v[2], v[5], v[3])
    glNormal3fv(normal)
    glBegin(GL_QUADS)
    glVertex3fv(v[0])
    glVertex3fv(v[2])
    glVertex3fv(v[5])
    glVertex3fv(v[3])
    glEnd()

    # Frente
    normal = ObtainTriangleFaceNormal(v[0], v[2], v[1])
    glNormal3fv(normal)
    glBegin(GL_TRIANGLES)
    glVertex3fv(v[0])
    glVertex3fv(v[2])
    glVertex3fv(v[1])
    glEnd()

    # Trás
    normal = ObtainTriangleFaceNormal(v[3], v[4], v[5])
    glNormal3fv(normal)
    glBegin(GL_TRIANGLES)
    glVertex3fv(v[3])
    glVertex3fv(v[4])
    glVertex3fv(v[5])
    glEnd()


def normalize(n, x, y, z):
    l = 0.0
    l = (x * x + y * y + z * z) ** (1 / 2)
    if l == 0.0:
        return n
    n[0] = x / l
    n[1] = y / l
    n[2] = z / l
    return n


def DrawTower(tower_color, roof_color, x, y):
    # Torre
    glPushMatrix()
    glTranslatef(x, 0.0, y)
    glRotated(-90.0, 1, 0, 0)
    glColor3f(*tower_color)
    glutSolidCylinder(1.4, 6.0, 12, 1)
    glRotated(90.0, 1, 0, 0)
    # Telhado
    glColor3f(*roof_color)
    glTranslatef(0.0, 6.0, 0.0)
    glRotated(-90.0, 1, 0, 0)
    glutSolidCone(1.9, 2.1, 12, 12)
    glPopMatrix()


def DrawWall(wall_color, x, y, u, v):
    glPushMatrix()
    glColor3f(0.3, 0.3, 0.3)
    glTranslatef(x, 1.8, y)
    glScaled(u, 3.6, v)
    glutSolidCube(1.0)
    glPopMatrix()


class Flake:
    def __init__(self):
        self.viva
        self.vida
        self.desaparecer
        self.xPos
        self.yPos
        self.zPos
        self.vel
        self.gravidade
