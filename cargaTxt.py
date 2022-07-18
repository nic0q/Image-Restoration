import numpy as np
from matplotlib import pyplot as plt

# Se genera la figura para mostrar más de 1 sola imagen
fig = plt.figure(figsize=(10, 7))
rows = 1
columns = 3  # Se visualiza en 3 filas y 1 sola columna
# volviendo a cargar la imagen.txt que esta en el disco
restored = np.loadtxt("restored.txt", dtype=np.float64)
# volviendo a cargar la imagen.txt que esta en el disco
corrupted = np.loadtxt("image_corrupted.txt", dtype=np.float64)
# volviendo a cargar la imagen.txt que esta en el disco
original = np.loadtxt("image_original.txt", dtype=np.float64)
original = original.reshape((256, 256))  # pasa de ser 1d a 2d
corrupted = corrupted.reshape((256, 256))  # pasa de ser 1d a 2d
restored = restored.reshape((256, 256))  # pasa de ser 1d a 2d
plt.gray()  # para que se vea en escala de grises
fig.add_subplot(rows, columns, 1)
plt.imshow(original)   # Imagen original
plt.axis('off')
plt.title("Original")
fig.add_subplot(rows, columns, 2)
plt.imshow(corrupted)  # Imagen corrupta
plt.axis('off')
plt.title("Corrupted")
fig.add_subplot(rows, columns, 3)
plt.imshow(restored)  # Imagen restaurada
plt.axis('off')
plt.title("Restored")
plt.show()
