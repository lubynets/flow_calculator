#ifndef FLOW_DRAWING_TOOLS_QNTOOLS_HELPER_HPP_
#define FLOW_DRAWING_TOOLS_QNTOOLS_HELPER_HPP_

#include <QnTools/DataContainer.hpp>

// template <typename T>
static int GetAxisNumber(Qn::DataContainerStatCalculate* data_container, std::string axis_name) {
  int number = 0;
  for(auto& axis : data_container->GetAxes()) {
    if(axis.Name() == axis_name) {
      return number;
    }
    number++;
  }
  throw std::runtime_error("No axis with name " + axis_name);
}

//template <typename T>
static int GetAxisSize(Qn::DataContainerStatCalculate* data_container, std::string axis_name) {
  return data_container->GetAxis(axis_name).size();
}

//template <typename T>
static int GetSymmetricCellNumber(Qn::DataContainerStatCalculate* data_container, int cell_number, int axis_number, int axis_size) {
  std::vector<size_t> indices = data_container->GetIndex(cell_number);
  indices.at(axis_number) = axis_size - 1 - indices.at(axis_number);
  return data_container->GetLinearIndex(indices);
}

//template <typename T>
static void SwapTwoCells(Qn::DataContainerStatCalculate* data_container, int a, int b) {
  Qn::StatCalculate buffer = data_container->At(a);
  data_container->At(a) = data_container->At(b);
  data_container->At(b) = buffer;
}

//template <typename T>
static void Reflect(Qn::DataContainerStatCalculate* data_container, std::string axis_name) {
  const int axis_number = GetAxisNumber(data_container, axis_name);
  const int axis_size = GetAxisSize(data_container, axis_name);
  const int data_container_size = data_container->size();

  std::vector<bool> done;
  for(int i=0; i<data_container_size; i++) {
    done.push_back(false);
  }

  for(int i=0; i<data_container_size; i++) {
    const int j = GetSymmetricCellNumber(data_container, i, axis_number, axis_size);
    if(done.at(i) == false && done.at(j) == false) {
      SwapTwoCells(data_container, i, j);
      done.at(i) = true;
      done.at(j) = true;
    }
  }
}

#endif // FLOW_DRAWING_TOOLS_QNTOOLS_HELPER_HPP_
