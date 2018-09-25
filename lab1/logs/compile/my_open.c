 #include <stdio.h>
main ( argc, argv )
int argc;
char *argv [];
{
char str[20];
scanf("%s", str);
if (str != NULL) {
  	if (fopen(str,"r") == NULL)
		printf("%s: неудача при попытке открыть файл %s",argv[0],str);
  	else
		printf("%s: файл %s открыт",argv[0],str);
} else
     printf("открываемый файл не указан");
}
