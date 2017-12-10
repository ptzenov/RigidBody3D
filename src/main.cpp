#include <memory>
#include <common.hpp>
#include <sim/controller.hpp>

#include <thread>
#include <graphics/renderer.hpp>

int main()
{

        //create the state of the object.
        //Set up the controller...
        Console_IO_Control controller {};
        SceneRenderer app {"app01"};
        app.createScene();

	std::thread loopT(&Console_IO_Control::loop,std::ref(controller));
	app.renderScene();	
	
	loopT.join();	

	
	/*
        // set one visualizer thread and one thread to interract with the user...
        omp_set_num_threads(OMP_NUM_THREADS);
        #pragma omp parallel
        {
                int tid = omp_get_thread_num();

                // initialize display window
                if(tid == THREAD_SIMULATION)
                {
                        app.renderScene();
                }
                else   // execute control loop
                {
                        controller.loop();
                }
        }
  
*/  
	return 0;

}


