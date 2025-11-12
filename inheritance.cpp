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

protected:
  int GetId() { return this->Id; };
  void SetId(int Id) { this->Id = Id; };
};

class Model : IdMixin {
public:
  Model() { this->SetId(IdStore::NextId()); };
  int Id() { return this->GetId(); };
};

int main(void) {
  Model m;
  std::cout << "Model.Id is - " << m.Id() << "!" << std::endl;
}
