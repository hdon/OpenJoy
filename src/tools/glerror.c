#ifdef __MACH__
#  include <OpenGL/gl.h>
#else
#  include <GL/gl.h>
#endif
#include <stdio.h>

void glError(char *s, unsigned int *errStore)
{
    while (1)
    {
        GLenum err = glGetError();
        if (err)
        {
            // We needn't continue if this function has already produced this
            // error, otherwise we end up printing a billion messages
            if (errStore && *errStore == err) return;

            // Store the error
            *errStore = err;

            // You can provide a string
            if (s) printf("%s: ", s);

            // These are the error messages that I happen to know of...
            switch (err)
            {
                case GL_INVALID_ENUM:
                    printf("glGetError(): invalid enum (error %i)\n", (unsigned int)err);
                    break;

                case GL_NO_ERROR:
                    printf("glGetError(): no error (error %i)\n", (unsigned int)err);
                    break;

                case GL_INVALID_VALUE:
                    printf("glGetError(): invalid value (error %i)\n", (unsigned int)err);
                    break;

                case GL_INVALID_OPERATION:
                    printf("glGetError(): invalid operation (error %i) (you"
                           " might be trying to query OpenGL for an error in"
                           " between glBegin() and glEnd()!!!)\n", (unsigned int)err);
                    break;

                case GL_STACK_UNDERFLOW:
                    printf("glGetError(): stack underflow (error %i)\n", (unsigned int)err);
                    break;

                case GL_STACK_OVERFLOW:
                    printf("glGetError(): stack overflow (error %i)\n", (unsigned int)err);
                    break;

#if 0
                case GL_TABLE_TOO_LARGE:
                    printf("glGetError(): table too large (error %i)\n", (unsigned int)err);
                    break;
#endif

                case GL_OUT_OF_MEMORY:
                    printf("glGetError(): out of memory (error %i)\n", (unsigned int)err);
                    break;

                default: 
                    printf( "glGetError(): Unknown Error (error %i)", (unsigned int)err);
                    break;
            }
        }
        else return;
    }
}

