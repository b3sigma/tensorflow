#include <stdio.h>
#include <stdlib.h>

#include "librungraph.h"
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/platform/env.h"

using namespace tensorflow;

bool simpletestfunction(float a, float b, float& result);
bool fulltestfunction(float a, float b, float& result);


_GR_EXTERN_ float testfunction(float a, float b) {
  printf("wow in testfunction!\n");
  float result = -1.0f;
  if(!simpletestfunction(a, b, result)) {
    printf("wow fucked\n");
  }
  return result;
}

bool simpletestfunction(float a, float b, float& result) {
  float c = a * b;
  printf("wow this worked and a='%f, b=%f, f(a,b)=%f\n", a, b, c);
  return true;
}

bool fulltestfunction(float aIn, float bIn, float& result) {
  // Initialize a tensorflow session
  Session* session;
  Status status = NewSession(SessionOptions(), &session);
  if (!status.ok()) {
    std::cout << status.ToString() << "\n";
    return false;
  }

  // Read in the protobuf graph we exported
  // (The path seems to be relative to the cwd. Keep this in mind
  // when using `bazel run` since the cwd isn't where you call
  // `bazel run` but from inside a temp folder.)
  GraphDef graph_def;
  status = ReadBinaryProto(Env::Default(), "models/graph.pb", &graph_def);
  if (!status.ok()) {
    std::cout << status.ToString() << "\n";
    return false;
  }

  // Add the graph to the session
  status = session->Create(graph_def);
  if (!status.ok()) {
    std::cout << status.ToString() << "\n";
    return false;
  }

  // Setup inputs and outputs:

  // Our graph doesn't require any inputs, since it specifies default values,
  // but we'll change an input to demonstrate.
  Tensor a(DT_FLOAT, TensorShape());
  a.scalar<float>()() = aIn;

  Tensor b(DT_FLOAT, TensorShape());
  b.scalar<float>()() = bIn;

  std::vector<std::pair<string, tensorflow::Tensor>> inputs = {
    { "a", a },
    { "b", b },
  };

  // The session will initialize the outputs
  std::vector<tensorflow::Tensor> outputs;

  // Run the session, evaluating our "c" operation from the graph
  status = session->Run(inputs, {"c"}, {}, &outputs);
  if (!status.ok()) {
    std::cout << status.ToString() << "\n";
    return false;
  }

  // Grab the first output (we only evaluated one graph node: "c")
  // and convert the node to a scalar representation.
  auto output_c = outputs[0].scalar<float>();
  result = (float)output_c(0);

  // (There are similar methods for vectors and matrices here:
  // https://github.com/tensorflow/tensorflow/blob/master/tensorflow/core/public/tensor.h)

  // Print the results
  std::cout << outputs[0].DebugString() << "\n"; // Tensor<type: float shape: [] values: 30>
  std::cout << output_c() << "\n"; // 30

  // Free any resources used by the session
  session->Close();


  return true;
}
