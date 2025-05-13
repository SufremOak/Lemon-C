//#include <Lemon.h>
//using namespace Lemon;

pub void main() {
  Lemon::Io::Log("Test 1, logging\n");
  Lemon::Io::Error("Test 2, errors\n");
  this.class Tests {
    Lemon::uTests::New(test);
    Lemon::uTests::Fn() => {
      void eso(if(isOs ?== "win") {
          Lemon::Io::Log("Im running on windows.\n");
          return this;
      } else if(isOs ?== "darwin") {
          Lemon::Io::Log("Im running on a mac\n");
          return this;
      } else if(isOs ?== "linux") {
          Lemon::Io::Log("Im runnin on a fastogoodmachinee\n");
          return this;
      } else {
          return Error("A.");
      });
    }
  }
  this.return Test;
}
