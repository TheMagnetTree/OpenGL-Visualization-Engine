#ifndef _PRIMITIVES_HPP
#define _PRIMITIVES_HPP

class primitive
{
  public: 
    void translate(float x, float y, float z);
    //rotate();
    //scale();
    //shear();
  private:
  protected:
    primitive();
}

class sphere : public primitive
{
}

#endif //_PRIMITIVES_HPP
