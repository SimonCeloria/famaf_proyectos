.data
	.equ SCREEN_WIDTH,   640
	.equ SCREEN_HEIGH,   480
	.equ BITS_PER_PIXEL, 32

	.equ GPIO_BASE,    0x3f200000
	.equ GPIO_GPFSEL0, 0x00
	.equ GPIO_GPLEV0,  0x34

	.globl main

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FIGURAS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

// Funcion que pinta un pixel

pintar_pixel:
    mov x0,x20
    cmp x2, SCREEN_WIDTH
    b.hs end_draw_pixel
    cmp x3,SCREEN_HEIGH
    b.hs end_draw_pixel
    mov x7,SCREEN_WIDTH
    madd x7,x3,x7,x2
    mov x8,x7
    lsl x8,x8,#2
    add x0,x0,x8
    stur w10,[x0]
end_draw_pixel:

    br lr //return

// Funcion que dibuja linea horizontal

linea_horizontal:
    sub sp,sp,#16
    stur lr,[sp,8]
    stur x2,[sp]

    loop_linea_horizontal:
        cmp x2,x4
        b.gt end_loop_horizontal
        bl pintar_pixel
        add x2,x2,#1
        b loop_linea_horizontal

    end_loop_horizontal:
        ldur lr,[sp,#8]
        ldur x2,[sp]
        add sp,sp,#16

        br lr //return


//Funcion que dibuja cuadrados/rectangulos
cuadrado:
    mov x0,x20          // x0 direccion de inicio
	add x0, x0, x4      // dirección de inicio + (x + (y*640))
    mov x3,x0
    
    mov x2,0            // Primer pixel y
set2:
    mov x1,0            // Primer pixel x
set1:
     stur w5,[x0]       // Pinto (w5 lee los 32 bits del registro x5 donde anteriormente guarde el color para pintar)
     add x0,x0,4        // Avanzo al la siguiene posicion en la matriz 
     add x1,x1,1        // Sumo 1 a x (x = cantidad de veces que ejecuto el loop)
     cmp x1,x25         // Si no es igual a x25 sigo recorriendo la fila
     b.ne set1
     add x3,x3,2560     // Salto un renglon
     mov x0,x3          // Nueva posicion del framebuffer
     add x2,x2,1        // Avanzo en y
     cmp x2,x26         // Si no es igual a x26 vuelvo a pintar
     b.ne set2
     br x30

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Circulos ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

// Parametros
// x6 y x7  coordenada x e y del centro del circulo
// x4 punto inicial offset
// x11 radio

circulos:
    mov x0,x20          //x0 direccion de inicio
    add x0,x0,x4        //direccion de inicio + dir cuadrado que contiene al circulo
    mov x3,x0
    mov x6,x11          //Coordenada x del centro del circulo radio x11
    mov x7,x11          //Coordenada y del centro del circulo radio x11
    mul x12,x11,x11     //Radio al cuadrado

    mov x2,0            //Primer pixel y
setc:
    mov x1,0            //Primer pixel x
setc2:
    sub x8 , x6, x1     // x8 = x6 - 0
    mul x8, x8, x8      // x8 = (x6 - 0)^2
    sub x9, x7, x2      // x9 = x11 - 0
    mul x9, x9, x9      // x9 = (x11 - 0)^2
    add x21, x8, x9     // x21 = (x-x0)^2 + (y-y0)^2
    cmp x21, x12        // Me fijo si es menor o igual al radio al cuadrado x11^2
    b.le pintar_circulo
    add x0,x0,4         // siguiente pixel
    add x1,x1,1         // recorro eje x
    cmp x1, x25         // pinto mientras x sea distinto 
    b.ne setc2

ir_a_y:
    add x3,x3,2560      // x3= x3 + (640+0)4
    mov x0,x3
    add x2,x2,1         // recorro eje y
    cmp x2,x26          // mientras y sea distinto 
    b.ne setc
    br x30

pintar_circulo:
    stur w5, [x0]
    add x0, x0, 4       // Siguiente pixel
    add x1, x1, 1       // Incremento x   
    cmp x1, x25
    b.ne setc2          // Si es el final del cuadrado vuelvo al loop Principal
    b ir_a_y             // Vuelvo a ver la condicion

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TRIANGULO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

equilatero:
    sub sp,sp,#8
    stur lr,[sp]

    loop_equilatero:
        bl linea_horizontal
        sub x2,x2,#1
        add x3,x3,#1
        add x4,x4,#1
        cmp x3,x5
        b.gt end_loop_equilatero
        bl loop_equilatero
    end_loop_equilatero:
    ldur lr,[sp]
    add sp,sp,#8

    br lr //return

//~~~~~~~~~~~~~~~~~~~~~~~~~~ MAIN ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

main:

	mov x20, x0  // Guarda la dirección base del framebuffer en x20

    mov x23, 0  //Contador para cambiar color
    mov w18, 0  // para comparacion
    mov x27, 0  // Contador para mover hacia arriba la nave
    mov x28, 0  // Contador para mover hacia abajo la nave
    mov x17, 0  // Contador para mover hacia la derecha la nave
    mov x14, 0  // Contafor para mover hacia la izquierda la nave

dibujarpant:

    mov x15, 0  // seteamos en 0 comparador de estrellas - color
    

// Printeo "el espacio" usando la funcion de cuadrados

    movz x5, 0x0E, lsl 16       //espacio deep-space
    movk x5, 0x202E, lsl 00
    mov x25, 640                // Ancho de la pantalla
    mov x26, 310                // hasta que llegue a la parte en que empiezo a pintar marte
    movz x4, 0x00, lsl 16       // Dirección de inicio + 0 -> Printea desde la direccion base del framebuffer
    movk x4, 0x0000, lsl 00 
    bl cuadrado

// Printeo "marte" usando la funcion de cuadrados

    movz x5, 0x64, lsl 16       // marte red-mars 
    movk x5, 0x1F15, lsl 00
    mov x25, 640                // Mismo ancho que el fondo
    mov x26, 180                // Pinto hasta el final de la pantalla
    movz x4, 0xB, lsl 16        // Empieza en Dirección = Dirección de inicio + 4 * [x + (y * 640)] con y = 300 x = 0
    movk x4, 0xC000, lsl 00     // Dirección = Dirección de inicio + 768,000 
    bl cuadrado		



//~~~~~~~~~~~~~~~~~~~ Printeo "estrellas" usando la funcion circulos ~~~~~~~~~~~~~~~~~~~~//

estrellas:
// Primera hilera de estrellas


    movz x5, 0xD5, lsl 16       // amarillo estrellas 
    movk x5, 0xAB55, lsl 00
    add x5,x5,x15               // Cambia el color de las estrellas

    mov x11, 7
    mov x13, 5                  // Cantidad de circulos que imprime
    movz x4, 0x1, lsl 16        // Posicion en la que imprime al primero
    movk x4, 0xF400, lsl 00     // Posicion en la que imprime al primero
stars:
    bl circulos
    add x4, x4, 2048            // Distancia entre cada circulo
    sub x13, x13, 1             // "Ya imprimi una estrella" entonces le resto una estrella al contador

    cbnz x13, stars 

// Segunda hilera de estrellas
    movz x5, 0xFF, lsl 16
    movk x5, 0xFFFF, lsl 00      // La hilera mas pequeña son estrellas blancas
    add x5,x5,x15               // Cambia el color de las estrellas

    mov x11, 3
    mov x13, 3                   //Cantidad de circulos que imprime
    movz x4, 0x00, lsl 16        //Posicion en la que imprime al primero
    movk x4, 0x5320, lsl 00
stars2:
    bl circulos
    add x4, x4, 2040             // Distancia entre cada circulo
    sub x13, x13, 1              // "Ya imprimi una estrella" entonces le resto una estrella al contador

    cbnz x13, stars2 

// Tercera hilera de estrellas
    movz x5, 0xD5, lsl 16       // Amarillo estrellas 
    movk x5, 0xAB55, lsl 00
    add x5,x5,x15               // Cambia el color de las estrellas

    mov x11, 9
    mov x13, 3                   // Cantidad de circulos que imprime
    movz x4, 0x3, lsl 16         // osicion en la que imprime al primero
    movk x4, 0xEAA0, lsl 00
stars3:
    bl circulos
    add x4, x4, 2040            // Distancia entre cada circulo
    sub x13, x13, 1             // "Ya imprimi una estrella" entonces le resto una estrella al contador

    cbnz x13, stars3 

// Ultima hilera de estrellas
    movz x5, 0xD5, lsl 16       // Amarillo estrellas 
    movk x5, 0xAB55, lsl 00
    add x5,x5,x15               // Cambia el color de las estrellas

    mov x11, 7
    mov x13, 1                  // Cantidad de circulos que imprime
    movz x4, 0x9, lsl 16        // Posicion en la que imprime al primero
    movk x4, 0x9A80, lsl 00
starslast:
    bl circulos
    add x4, x4, 2040            // Distancia entre cada circulo
    sub x13, x13, 1             // "Ya imprimi una estrella" entonces le resto una estrella al contador

    cbnz x13, starslast 

    cbnz x15, depuesdeestrellas // Si no es cero salta al loop

//~~~~~~~~~~~~~~~~~~~ Printeo "deimos"  ~~~~~~~~~~~~~~~~~~~~//

    movz x5, 0xC2, lsl 16        // Color deimos 
    movk x5, 0xAF97, lsl 00
    mov x11, 64                  // Radio
    movz x4, 0x5, lsl 16
    movk x4, 0x6400, lsl 00      // Posicion inicial
    bl circulos

//~~~~~~~~~~~~~~~~~~~ Printeo "phobos"  ~~~~~~~~~~~~~~~~~~~~//

    movz x5, 0x84, lsl 16       // Color phobos 
    movk x5, 0x6958, lsl 00
    add x5,x5,x23               // Para cambiar el color de phobos

    mov x11, 128                // Radio
    movz x4, 0x4, lsl 16
    movk x4, 0xB3C0, lsl 00     // Posicion inicial
    bl circulos

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ NAVE  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    
    //FUEGO (Triangulo)
    mov x2,480
    mov x3,360
    mov x4,480
    mov x5,380


    // Mueve el fuego en el eje Y hacia arriba
    sub x3,x3,x27 
    sub x5,x5,x27

    // Mueve el fuego en el eje Y hacia abajo
    add x3,x3,x28
    add x5,x5,x28

    // Mueve el fuego en el eje X hacia la derecha
    add x2,x2,x17
    add x4,x4,x17

    // Mueve el fuego en el eje X hacia la izquierda
    sub x2,x2,x14
    sub x4,x4,x14

    movz x10, 0xaa, lsl 16
    movk x10, 0x4203, lsl 00    // Color del fuego
    bl equilatero

    //FUEGO PEQUEÑO (Triangulo)

    mov x2,480
    mov x3,360
    mov x4,480
    mov x5,370


    // Mueve el fuego en el eje Y hacia arriba
    sub x3,x3,x27 
    sub x5,x5,x27

    // Mueve el fuego en el eje Y hacia abajo
    add x3,x3,x28
    add x5,x5,x28

    // Mueve el fuego en el eje X hacia la derecha
    add x2,x2,x17
    add x4,x4,x17

    // Mueve el fuego en el eje X hacia la izquierda
    sub x2,x2,x14
    sub x4,x4,x14

    movz x10, 0xFF, lsl 16
    movk x10, 0xFF00, lsl 00    // Color del fuego
    bl equilatero


    //COHETE DERECHO
    mov x2,510
    mov x3,340
    mov x4,510
    mov x5,360


    // Mueve la nave en el eje Y hacia arriba
    sub x3,x3,x27 
    sub x5,x5,x27

    // Mueve la nave en el eje Y hacia abajo
    add x3,x3,x28
    add x5,x5,x28

    // Mueve la nave en el eje X hacia la derecha
    add x2,x2,x17
    add x4,x4,x17

    // Mueve la nave en el eje X hacia la izquierda
    sub x2,x2,x14
    sub x4,x4,x14

    movz x10, 0x7c, lsl 16
    movk x10, 0x7d7f, lsl 00       // Color de la nave
    bl equilatero



    //COHETE IZQUIERDO

    mov x2,450                    //Posicion x
    mov x3,340                    //Posicion y
    mov x4,450  
    mov x5,360                    //Tamaño


    // Mueve la nave en el eje Y hacia arriba
    sub x3,x3,x27 
    sub x5,x5,x27

    // Mueve la nave en el eje Y hacia abajo
    add x3,x3,x28
    add x5,x5,x28

    // Mueve la nave en el eje X hacia la derecha
    add x2,x2,x17
    add x4,x4,x17

    // Mueve la nave en el eje X hacia la izquierda
    sub x2,x2,x14
    sub x4,x4,x14

    movz x10, 0x7c, lsl 16
    movk x10, 0x7d7f, lsl 00    // Color de la nave
    bl equilatero

    //CENTRO NAVE

    mov x2,480
    mov x3,320
    mov x4,480
    mov x5,360

    // Mueve la nave en el eje Y hacia arriba
    sub x3,x3,x27 
    sub x5,x5,x27

    // Mueve la nave en el eje Y hacia abajo
    add x3,x3,x28
    add x5,x5,x28

    // Mueve la nave en el eje X hacia la derecha
    add x2,x2,x17
    add x4,x4,x17

    // Mueve la nave en el eje X hacia la izquierda
    sub x2,x2,x14
    sub x4,x4,x14

    movz x10, 0x7c, lsl 16
    movk x10, 0x7d7f, lsl 00    // Color de la nave
    bl equilatero




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//






//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GPIO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

loop:

    //~~~~~~ ANIMACION CAMBIAN DE COLOR LAS ESTRELLAS ~~~~~~//
    cbnz x15, estrellas
depuesdeestrellas:

    
    mov x24, GPIO_BASE
    ldr w22, [x24, GPIO_GPLEV0]
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


// TECLA W - MOVER A ARRIBA LA NAVE
    and w29, w22,0x00000002      // Me fijo si la barra espaciadora esta apretada
    cbnz w29, arriba             // decremento eje Y
    b omitir
arriba:
    add x27, x27, 5              // Muevo la posicion Y de la nave
    add x11,x11,10
    b dibujarpant
omitir:

// TECLA S - MOVER A LA ABAJO LA NAVE
    and w29, w22, 0x00000008
    cbnz w29, abajo
    b omitir2
abajo:
    add x28, x28, 5
    b dibujarpant
omitir2:

// TECLA D - MOVER A LA DERECHA LA NAVE
    and w29, w22, 0x00000010
    cbnz w29, derecha
    b omitir3
derecha:
    add x17, x17, 5
    b dibujarpant
omitir3:

// TECLA A - MOVER A LA DERECHA LA NAVE
    and w29, w22, 0x00000004
    cbnz w29, izquierda
    b omitir4
izquierda:
    add x14, x14, 5
    b dibujarpant
omitir4:



// TECLA BARRA ESPACIADORA -> CAMBIA DE COLOR LA NAVE 

    and w19, w22,0x00000020      // Me fijo si la barra espaciadora esta apretada, para que cambie solo una vez el color
    sub w16,w18,w19              // w16 = w18 - w19
    cbnz w16, segundacondicion   // w18 == w19?
    b omitir5                    // si son iguales ni me fijo en la segunda condicion
segundacondicion:                //si no
    mov w18,w19                  // Guardo temporalmente el valor de w19  en w18, para luego compararlo
    sub w19,w19,0x00000020       // veo si la tecla está apretada
    add x23, x23, 5              // Cambio el color de "phobos" sumando al contador
    cbz w19, dibujarpant
omitir5:

    add x15,x15,10               // Contador estrellas

    b loop  
    
InfLoop:
	b InfLoop
