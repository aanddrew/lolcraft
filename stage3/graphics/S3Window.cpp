if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("Failed to init SDL\n");
  }

    //opengl shit===========
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    //we need to enable depth buffer?
    //aparently set to 16 bits by defualt

  //create a window, the last flag says its gonna be an opengl context
  SDL_Window* window = SDL_CreateWindow(
    "OPENGL Window",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    WIDTH,
    HEIGHT,
    SDL_WINDOW_OPENGL
  );

  //create context
  SDL_GLContext mainContext = SDL_GL_CreateContext(window);

  glEnable(GL_DEPTH_TEST);

  //this is critical, seg fault happens without it
  glewExperimental = GL_TRUE; 
  glewInit();