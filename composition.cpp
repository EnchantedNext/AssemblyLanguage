#include <iostream>

class IdStore {
public:
  static int NextId() {
    Id++;
    return Id;
  };

private:
  static int Id;
};

int IdStore::Id = 0;

class IdMixin {
private:
  int Id;

public:
  int GetId() { return this->Id; };
  void SetId(int Id) { this->Id = Id; };
};

class Model {
public:
  Model() {
    this->IdScope = IdMixin();
    this->IdScope.SetId(IdStore::NextId());
  };
  int Id() { return this->IdScope.GetId(); };

private:
  IdMixin IdScope;
};

int main(void) {
  Model m;
  std::cout << "First Model.Id is - " << m.Id() << "!" << std::endl;
  Model _m;
  std::cout << "Second Model.Id is - " << _m.Id() << "!" << std::endl;
}
