/*
OpenCL vector addition.
Provided by this stack overflow post:
https://stackoverflow.com/questions/26517114/how-to-compile-opencl-project-with-kernels
*/


#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <cstdlib>
#include <vector>
#include <CL/cl.hpp>

int main(int argc, char **argv) {

  const int N_ELEMENTS = 1024*1024;
  unsigned int platform_id = 0, device_id = 0;

  try {
    std::unique_ptr<int[]> A(new int[N_ELEMENTS]);
    std::unique_ptr<int[]> B(new int[N_ELEMENTS]);
    std::unique_ptr<int[]> C(new int[N_ELEMENTS]);

    for (int i = 0; i < N_ELEMENTS; ++i)
    {
      A[i] = i;
      B[i] = i;
    }


    // Query for platforms
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    // Get a list of devices on this platforms
    std::vector<cl::Device> devices;
    platforms[platform_id].getDevices(CL_DEVICE_TYPE_GPU|CL_DEVICE_TYPE_CPU, &devices);

    // Create a context
    cl::Context context(devices);

    // Create command queue
    cl::CommandQueue queue = cl::CommandQueue(context, devices[device_id]);

    // Create the memory buffers
    cl::Buffer bufferA = cl::Buffer(context, CL_MEM_READ_ONLY, N_ELEMENTS * sizeof(int));
    cl::Buffer bufferB = cl::Buffer(context, CL_MEM_READ_ONLY, N_ELEMENTS * sizeof(int));
    cl::Buffer bufferC = cl::Buffer(context, CL_MEM_WRITE_ONLY, N_ELEMENTS * sizeof(int));

    // Copy the input data to the input buffers using the command queue.
    queue.enqueueWriteBuffer(bufferA, CL_FALSE, 0, N_ELEMENTS * sizeof(int));
    queue.enqueueWriteBuffer(bufferB, CL_FALSE, 0, N_ELEMENTS * sizeof(int));

    // Read the program source.
    std::ifstream sourceFile("vector_add_kernel.cl")
    std::string sourceCode(std::isstreambuf_iterator<char>(sourceFile), (std::istreambuf_iterator<char>()));
    cl::Program::Sources source(1, std::make_pair(sourceCode.c_str(), sourceCode.length()));

    // Make program from the source code
    cl::Program program=cl::Program(context, source);

    // Build the program for the devices.
    program.build(devices);

    // Make kernel
    cl::Kernel vecadd_kernel(program, "vecadd");

    // Set the kernel arguments.
    vecadd_kernel.setArg(0, bufferA);
    vecadd_kernel.setArg(1, bufferB);
    vecadd_kernel.setArg(2, bufferC);

    // Execute the kernel
    cl::NDRange global(N_ELEMENTS);
    cl::NDRange local(256);
    queue.enqueueNDRangeKernel(vecadd_kernel, cl::NullRange, global, local);

    // Copy the output data back to the host
    queue.enqueueReadBuffer(bufferC, CL_TRUE, 0, N_ELEMENTS * sizeof(int), C.get());

    // Verify the result
    bool result = true;
    for (int i = 0; i < N_ELEMENTS; ++i)
    {
      if (C[i] != A[i] + B[i])
      {
        result = false;
        break;
      }
    }
    if (result)
      std::cout<<"Success! \n";
    else
      std::cout<<"Failes! \n";
  }
  catch(cl::Error err) {
    std::cout << "Error: " << err.what() << "(" << err.err() << ")" << std::endl;
    return(EXIT_FAILURE);
  }
  std::cout << "Done. \n";
  return( EXIT_SUCCESS );



}
