import scipy
import numpy as np
from matplotlib import pyplot as plt
from skimage.transform import resize

x = scipy.misc.face()  # la imagen de prueba
x = np.array(x, dtype=np.float64)  # asegurandose que son float
# la tercera dimension da cuenta de los tres colores rgb, dejamos solo el rojo
x = x[:, :, 0]
x = x.reshape(768, 1024)
# para que los numero queden entre 0 y 1 el algoritmo funciona mejor asi
x = x/np.max(x)
x = resize(x, (256, int(256*1024/768)))  # cambiando el tamaño segun regla de 3
x = x[:, :256]  # recortando
y = x
# generamos un archivo con los valores de la imagen
x = x.reshape(256*256)  # aplanando los datos
np.savetxt("image.txt", x, fmt="%1.12lf")
# mostramos la imagen
plt.gray()  # en escala de grises
plt.imshow(y)
plt.show()