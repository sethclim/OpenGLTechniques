#ifndef UNMANAGED
#define UNMANAGED

class Unmanaged_Class
{
public:

    Unmanaged_Class();

    /*This is the method that is to be called from Managed code*/
    void methodToBeCalledInUnmanaged(int data);
};

#endif