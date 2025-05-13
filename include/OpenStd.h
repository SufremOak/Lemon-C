#ifndef OPENSTD_H
#define OPENSTD_H

#ifdef _cplusplus
  #include <iostream>
  #include <stdio.h>

  namespace stdoss {
    namespace io {
      // TODO: std::cout-like thing
      void cout();
      // TODO: stderr equivalation
      void err() {
        // ...
      }
    }
  }
#endif

#endif // OPENSTD_H
