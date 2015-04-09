echo "compiling Example 1";
g++ Example_1_implement_thread.cpp Thread.cpp -pthread -o Example_1_implement_thread.out
echo "compiling Example 2";
g++ Example_2_anonymous_class.cpp Thread.cpp -lpthread -o Example_2_anonymous_class.out
echo "compiling Example 3";
g++ Example_3_uncontrolled_synchronizer.cpp Thread.cpp -lpthread -o Example_3_uncontrolled_synchronizer.out
echo "compiling Example 4";
g++ Example_4_wait_notify.cpp Thread.cpp -lpthread -o Example_4_wait_notify.out
echo "compiling Example 5";
g++ Example_5_controlled_synchronizer.cpp Thread.cpp -lpthread -o Example_5_controlled_synchronizer.out
echo "compiling Example 6";
g++ Example_6_get_status.cpp Thread.cpp -lpthread -o Example_6_get_status.out

echo "Finished !!!";
