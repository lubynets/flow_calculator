//
// Created by mikhail on 7/30/21.
//

#ifndef QNANALYSIS_SRC_QNANALYSISCALCULATE_CORRELATION_HPP_
#define QNANALYSIS_SRC_QNANALYSISCALCULATE_CORRELATION_HPP_

#include <QnTools/DataContainer.hpp>
#include <TFile.h>
#include <TObject.h>

class Correlation : public TObject {
 public:
  Correlation() = default;
  Correlation(TFile* file,
              const std::string& directory,
              const std::vector<std::string>& vector_names,
              const std::vector<std::string>& component_names);
  Correlation(const Correlation&) = default;
  ~Correlation() override = default;
  void AddComponent( const Qn::DataContainerStatCalculate& component, const std::string& name ){
    components_.push_back( component );
    component_names_.push_back(name);
  }
  void RemoveComponent( size_t idx ){
    assert(idx < components_.size());
    auto it = components_.begin()+idx;
    components_.erase(it);
    assert(idx < component_names_.size());
    auto it_names = component_names_.begin()+idx;
    component_names_.erase(it_names);
  }
  Qn::DataContainerStatCalculate& operator[]( size_t idx ){return components_.at(idx);};
  [[nodiscard]] const std::string &Title() const { return title_; }
  [[nodiscard]] std::vector<std::string> &GetComponentNames() {
    return component_names_;
  }
  [[nodiscard]] std::vector<std::string> &GetVectorNames() {
    return vector_names_;
  }
  size_t Size(){ return components_.size(); };
  void SetTitle(const std::string &titles) { title_ = titles; }
  void SetComponentNames(const std::vector<std::string> &component_names) {
    component_names_ = component_names;
  }
  void Save( const std::string& name ){
    int idx=0;
    for( auto component : components_ ){
      component.Write( std::data(name+"."+component_names_.at(idx)) );
      idx++;
    }
  }
  friend Correlation operator+( const Correlation&, const Correlation& );
  friend Correlation operator-( const Correlation&, const Correlation& );
  friend Correlation operator*( const Correlation&, const Correlation& );
  friend Correlation operator*( const Correlation&, const std::vector<double>& );
  friend Correlation operator*( const Correlation&, double );
  friend Correlation operator/( const Correlation&, const Correlation& );
  friend Correlation operator/( const Correlation&, double );
  friend Correlation Sqrt( const Correlation& );
  friend Correlation MatrixMultiply( const Correlation&, const Correlation& );
  friend Correlation Mirror( const Correlation&, std::string axis_name);
protected:
  std::vector<Qn::DataContainerStatCalculate> components_;
  std::string title_;
  std::vector<std::string> component_names_;
  std::vector<std::string> vector_names_;
  ClassDefOverride(Correlation, 1)
};

#endif//QNANALYSIS_SRC_QNANALYSISCALCULATE_CORRELATION_HPP_
