class ZeroEvenOdd {
private:
    int n;
    bool _print_0 = true;
    bool _print_even = true;
    mutex _mutex;
    condition_variable _cv;
    int _cur = 1;
public:
    ZeroEvenOdd(int n) {
        this->n = n;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        //while(_cur < n)
        for(int i = 0; i < n ; i++)
        {
            unique_lock<mutex> ul(_mutex);
            while(!_print_0)
                _cv.wait(ul);
            cout<<0<<endl;
            _print_0 = false;
            _cv.notify_all();
        }
        cout<<"zero end"<<endl;
    }

    void even(function<void(int)> printNumber) {
        while(_cur < n)
        {
            unique_lock<mutex> ul(_mutex);
            while(_print_0 || !_print_even)
                _cv.wait(ul);

            //printNumber(1);
            cout<<_cur++<<endl;
            _print_0 = true;
            _print_even = false;
            _cv.notify_all();
            cout<<"notify all end"<<_cur<<endl;
        }
        cout<<"even end "<<_cur<<endl;
    }

    void odd(function<void(int)> printNumber) {
        while(_cur < n)
        {
            unique_lock<mutex> ul(_mutex);
            while(_print_0 || _print_even)
                _cv.wait(ul);
            cout<<"odd wait end"<<_cur<<endl;
            _print_0 = true;
            _print_even = true;
            cout<<_cur++<<endl;
            //printNumber(2);
            _cv.notify_all();
        }
        cout<<"odd end "<<_cur<<endl;
    }
};

int main()
{
    
}