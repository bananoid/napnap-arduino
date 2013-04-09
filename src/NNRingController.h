class NNRingController{
private:
  int pin;
  unsigned long int timeOut;
public:
  NNRingController(int pin);
  void begin();
  void process();
};
