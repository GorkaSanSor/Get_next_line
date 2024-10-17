#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>  // Para usar open()

int	main(void)
{
	int		fd;
	char	*line;

	// Abrir el archivo test.txt
	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		// Si no se puede abrir el archivo, imprime un error
		write(2, "Error al abrir el archivo\n", 26);
		return (1);
	}

	// Llamar repetidamente a get_next_line y mostrar cada línea
	while ((line = ft_get_next_line(fd)) != NULL)
	{
		printf("%s", line);  // Depuración: imprimir la línea leída
		free(line);  // Libera la memoria de la línea leída
	}

	// Verificar si el bucle terminó sin leer nada
	if (line == NULL)

	// Cerrar el archivo después de terminar
	close(fd);
	return (0);
}
