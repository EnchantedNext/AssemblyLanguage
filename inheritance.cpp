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

protected:
  unsigned int GetId() { return this->Id; };
  void SetId(const unsigned int Id) { this->Id = Id; };
};

class Model : IdMixin {
public:
  Model() { this->SetId(IdStore::NextId()); };
  unsigned int Id() { return this->GetId(); };
};

int main(void) {
  Model m;
  std::cout << "Model.Id is - " << m.Id() << "!" << std::endl;
}
