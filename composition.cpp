#include <iostream>

class IdStore {
public:
  static unsigned int NextId() {
    Id++;
    return Id;
  };

private:
  static unsigned int Id;
};

unsigned int IdStore::Id = 0;

class IdMixin {
private:
  unsigned int Id;

public:
  unsigned int GetId() { return this->Id; };
  void SetId(const unsigned int Id) { this->Id = Id; };
};

class Model {
public:
  Model() {
    this->IdScope = IdMixin();
    this->IdScope.SetId(IdStore::NextId());
  };
  unsigned int Id() { return this->IdScope.GetId(); };

private:
  IdMixin IdScope;
};

int main(void) {
  Model m;
  std::cout << "First Model.Id is - " << m.Id() << "!" << std::endl;
  Model _m;
  std::cout << "Second Model.Id is - " << _m.Id() << "!" << std::endl;
}
