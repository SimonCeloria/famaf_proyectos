.data
	.equ SCREEN_WIDTH,   640
	.equ SCREEN_HEIGH,   480
	.equ BITS_PER_PIXEL, 32

	.equ GPIO_BASE,    0x3f200000
	.equ GPIO_GPFSEL0, 0x00
	.equ GPIO_GPLEV0,  0x34
    delay: .dword 0xfffff



	.globl main
	//.globl bloques

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FIGURAS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

// Funcion que pinta un pixel

draw_pixel:
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
        bl draw_pixel
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
    
    mov x2,0            //Primer pixel y
set2:
    mov x1,0            //Primer pixel x
set1:
     stur w5,[x0]       //Pinto (w5 lee los 32 bits del registro x5 donde anteriormente guarde el color para pintar)
     add x0,x0,4        //Avanzo al la siguiene posicion en la matriz 
     add x1,x1,1        //Sumo 1 a x (x = cantidad de veces que ejecuto el loop)
     cmp x1,x25         //Si no es igual a x25 sigo recorriendo la fila
     b.ne set1
     add x3,x3,2560     //Salto un renglon
     mov x0,x3          //Nueva posicion del framebuffer
     add x2,x2,1        //Avanzo en y
     cmp x2,x26         //Si no es igual a x26 vuelvo a pintar
     b.ne set2
     br x30

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Circulos ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

// x6 = coordenada x del centro del circulo
// x7 = coordenada y del centro del circulo
// x4 = punto inicial del cuadrado que contiene al circulo
// x11 = parametro de la coordenada x e y (radio)
// x12 = radio al cuadrado
// x25 = punto x final del cuadrado que contiene al circulo  
// x26 = punto y final del cuadrado que contiene al circulo
// x8, x9 y x21  =  resultados de operaciones

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
    sub x8 , x6, x1                     // x8 = x11 - 0
    mul x8, x8, x8                      // x8 = (x11 - 0)^2
    sub x9, x7, x2                      // x9 = x11 - 0
    mul x9, x9, x9                      // x4 = (x11 - 0)^2
    add x21, x8, x9                     // x5 = (x-x0)^2 + (y-y0)^2
    cmp x21, x12                        // Me fijo si es menor o igual al radio al cuadrado x11^2
    b.le drawcircle
    add x0,x0,4                         // siguiente pixel
    add x1,x1,1                         // recorro eje x
    cmp x1, x25                         // pinto mientras x sea distinto 
    b.ne setc2

gotoy:
    add x3,x3,2560                      // x3= x3 + (6401+0)4
    mov x0,x3
    add x2,x2,1                         // recorro eje y
    cmp x2,x26                          // mientras y sea distinto 
    b.ne setc
    br x30

drawcircle:
    stur w5, [x0]
    add x0, x0, 4                       // Siguiente pixel
    add x1, x1, 1                       // Incremento x   
    cmp x1, x25
    b.ne setc2                          // Si es el final del cuadrado vuelvo al loop Principal
    b gotoy                             // Vuelvo a ver la condicion

// Funcion que dibuja un triangulo

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




crearDelay:
        ldr x15, delay
    loop_crearDelay:
        subs x15, x15, 1
        b.ne loop_crearDelay

        br lr // return
//

    //~~~~~~~~~~~~~~~~~~~~~~~~~~ Main ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
main:
	// x0 contiene la direccion base del framebuffer
	mov x20, x0                 // Guarda la dirección base del framebuffer en x20

    mov x23, 0  //Contador para cambiar color
    //mov w10, 0  // para comparacion
    mov x27, 0 // Contador para mover hacia arriba la nave
    mov x28, 0 // Contador para mover hacia abajo la nave
    mov x22, 0 // Contador para mover hacia la derecha la nave

dibujarpant:

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



//~~~~~~~~~~~~~~~~~~~ Printeo "estrellas" usando la funcion circulos radio 6 ~~~~~~~~~~~~~~~~~~~~//


// Primera hilera de estrellas
    movz x5, 0xD5, lsl 16       // amarillo estrellas 
    movk x5, 0xAB55, lsl 00
    mov x11, 7
    mov x13, 5                  //Cantidad de circulos que imprime
    movz x4, 0x1, lsl 16        //Posicion en la que imprime al primero
    movk x4, 0xF400, lsl 00     //Posicion en la que imprime al primero
stars:
    bl circulos
    add x4, x4, 2048            // Distancia entre cada circulo
    sub x13, x13, 1             // "Ya imprimi una estrella" entonces le resto una estrella al contador

    cbnz x13, stars 

// Segunda hilera de estrellas
    movz x5, 0xFF, lsl 16
    movk x5, 0xFFFF, lsl 00      // La hilera mas pequeña son estrellas blancas
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
    movz x5, 0xD5, lsl 16        // amarillo estrellas 
    movk x5, 0xAB55, lsl 00
    mov x11, 9
    mov x13, 3                   //Cantidad de circulos que imprime
    movz x4, 0x3, lsl 16         //Posicion en la que imprime al primero
    movk x4, 0xEAA0, lsl 00
stars3:
    bl circulos
    add x4, x4, 2040            // Distancia entre cada circulo
    sub x13, x13, 1             // "Ya imprimi una estrella" entonces le resto una estrella al contador

    cbnz x13, stars3 

// Cuarta hilera de estrellas
    movz x5, 0xFF, lsl 16
    movk x5, 0xFFFF, lsl 00     // La hilera mas pequeña son estrellas blancas
    mov x11, 5
    mov x13, 3                  //Cantidad de circulos que imprime
    movz x4, 0x7, lsl 16        //Posicion en la que imprime al primero
    movk x4, 0xD4A0, lsl 00
stars4:
    bl circulos
    add x4, x4, 2040            // Distancia entre cada circulo
    sub x13, x13, 1             // "Ya imprimi una estrella" entonces le resto una estrella al contador

    cbnz x13, stars4 

// Ultima hilera de estrellas
    movz x5, 0xD5, lsl 16       // amarillo estrellas 
    movk x5, 0xAB55, lsl 00
    mov x11, 7
    mov x13, 2                  //Cantidad de circulos que imprime
    movz x4, 0x9, lsl 16        //Posicion en la que imprime al primero
    movk x4, 0x6A80, lsl 00
starslast:
    bl circulos
    add x4, x4, 2040            // Distancia entre cada circulo
    sub x13, x13, 1             // "Ya imprimi una estrella" entonces le resto una estrella al contador

    cbnz x13, starslast 


//~~~~~~~~~~~~~~~~~~~ Printeo "deimos"  ~~~~~~~~~~~~~~~~~~~~//

    movz x5, 0xC2, lsl 16        // Color deimos 
    movk x5, 0xAF97, lsl 00
    mov x11, 64                  // Radio
    movz x4, 0x5, lsl 16
    movk x4, 0x6400, lsl 00      // 4 *(320(240*640)) = 
    bl circulos

//~~~~~~~~~~~~~~~~~~~ Printeo "phobos"  ~~~~~~~~~~~~~~~~~~~~//

    movz x5, 0x84, lsl 16       // Color phobos 
    movk x5, 0x6958, lsl 00
    mov x11, 128                // Radio
    movz x4, 0x4, lsl 16
    movk x4, 0xB3C0, lsl 00     
    bl circulos




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Triangulo  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    
    //FUEGO
    //add x23, x23, 5 // Cambio el color sumando al contador
    //add x27, x27, 5 // Muevo el Y de la nave
    mov x2,480
    mov x3,360
    mov x4,480
    mov x5,380


    // Mueve la nave en el eje Y hacia arriba
    sub x3,x3,x27 
    sub x5,x5,x27

    // Mueve la nave en el eje Y hacia abajo
    add x3,x3,x28
    add x5,x5,x28

    // Mueve la nave en el eje X hacia la derecha
    add x2,x2,x22
    add x4,x4,x22

    movz x10, 0xaa, lsl 16
    movk x10, 0x4203, lsl 00    // Color de la nave
    //add x10, x10, x23   // Cambia el color de la nave
    bl equilatero

    //FUEGO PEQUEÑO
    //add x23, x23, 5 // Cambio el color sumando al contador
    //add x27, x27, 5 // Muevo el Y de la nave
    mov x2,480
    mov x3,360
    mov x4,480
    mov x5,370


    // Mueve la nave en el eje Y hacia arriba
    sub x3,x3,x27 
    sub x5,x5,x27

    // Mueve la nave en el eje Y hacia abajo
    add x3,x3,x28
    add x5,x5,x28

    // Mueve la nave en el eje X hacia la derecha
    add x2,x2,x22
    add x4,x4,x22

    movz x10, 0xFF, lsl 16
    movk x10, 0xFF00, lsl 00    // Color de la nave
    //add x10, x10, x23   // Cambia el color de la nave
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
    add x2,x2,x22
    add x4,x4,x22

    movz x10, 0x7c, lsl 16
    movk x10, 0x7d7f, lsl 00    // Color de la nave
    //add x10, x10, x23   // Cambia el color de la nave
    bl equilatero



    //COHETE IZQUIERDO

    mov x2,450
    mov x3,340
    mov x4,450
    mov x5,360


    // Mueve la nave en el eje Y hacia arriba
    sub x3,x3,x27 
    sub x5,x5,x27

    // Mueve la nave en el eje Y hacia abajo
    add x3,x3,x28
    add x5,x5,x28

    // Mueve la nave en el eje X hacia la derecha
    add x2,x2,x22
    add x4,x4,x22

    movz x10, 0x7c, lsl 16
    movk x10, 0x7d7f, lsl 00    // Color de la nave
    //add x10, x10, x23   // Cambia el color de la nave
    bl equilatero

    //NAVE

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
    add x2,x2,x22
    add x4,x4,x22

    movz x10, 0x7c, lsl 16
    movk x10, 0x7d7f, lsl 00    // Color de la nave
    //add x10, x10, x23   // Cambia el color de la nave
    bl equilatero



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GPIO ~~~~~~~~~~~~~~~~~~~~~~~~~//

// Tienen libres los registros x14 x17 x18 x19

//creo un delay de xffffff
bl crearDelay


// BARRA ESPACIADORA
loop:
//~~~~~~~~~ Hay que meter una animacion en el loop ~~~~~~~~~~~~~~~~~~~~//



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    mov x24, GPIO_BASE
    ldr w22, [x24, GPIO_GPLEV0]
//    and w16, w22,0x00000020  // Me fijo si la barra espaciadora esta apretada
//
//    // Para que cambie solo una vez el color
//    sub w27,w28,w16     // w27 = w28 - w16
//    cbnz w27, segundacondicion   // w28 == w16?
//    b omitir       // si son iguales ni me fijo en la segunda condicion
//segundacondicion:   //si no
//    mov w28,w16     // Guardo temporalmente el valor de w16  en w28, para luego compararlo
//    sub w16,w16,0x00000020  // veo si la tecla está apretada
//    cbz w16, dibujarpant
//omitir:


// TECLA W - VA PARA ARRIBA LA NAVE
    and w29, w22,0x00000002 // Me fijo si la barra espaciadora esta apretada
    cbnz w29, arriba//decrementoY
    b omitir
arriba:
    add x27, x27, 5 // Muevo el Y de la nave
    add x11,x11,10
    b dibujarpant
omitir:

// TECLA S - VA PARA ABAJO LA NAVE
    and w29, w22, 0x00000008
    cbnz w29, abajo
    b omitir2
abajo:
    add x28, x28, 5
    b dibujarpant
omitir2:

// TECLA D - VA PARA LA DERECHA LA NAVE
    and w29, w22, 0x00000010
    cbnz w29, derecha
    b omitir3
derecha:
    add x22, x22, 5
    b dibujarpant
omitir3:

//    b omitir_2
//decrementoY:
//    sub x3,x3,x6 // Mueve la nave en el eje Y
//    sub x5,x5,x6
//    b dibujarpant
//omitir_2:
    b loop  
InfLoop:
	b InfLoop
