//
// Created by mikhail on 8/1/21.
//

#include "Functions.hpp"

ClassImp(Functions);

Correlation Functions::Resolution3S(const Correlation& numerator1, const Correlation& numerator2, const Correlation& denominator) {
  auto result = Sqrt(numerator1*numerator2/denominator);
  return result;
}

Correlation Functions::Resolution4S(const Correlation& first, const Correlation& second, const Correlation& third, const Correlation& fourth) {
  Correlation R4 = Resolution3S(first, third, fourth);
  return second/R4 * (-1.);
}

std::vector<Correlation> Functions::VectorResolutions3S(TFile* file,
                                                    const std::string& directory,
                                                    const std::string& ep_vector,
                                                    const std::vector<std::string>& res_vectors,
                                                    const std::vector<std::string>& comp_names){
  std::vector<Correlation> res_vector;
  auto qa = ep_vector;
  auto res_v = res_vectors;
  auto it = std::find( res_v.begin(), res_v.end(), qa );
  if (it != res_v.end()){
    res_v.erase(it);
  }
  for( size_t i=0; i<res_v.size(); ++i ){
    auto qb = res_v.at(i);
    for( size_t j=i+1; j<res_v.size(); ++j ){
      auto qc = res_v.at(j);
      Correlation qa_qb( file, directory, {qa, qb}, comp_names);
      Correlation qa_qc( file, directory, {qa, qc}, comp_names);
      Correlation qb_qc( file, directory, {qb, qc}, comp_names);

      auto res_qa = Functions::Resolution3S( qa_qb*2, qa_qc*2, qb_qc*2 );
      res_qa.SetTitle( qa+"("+qb+","+qc+")" );
      res_vector.emplace_back(res_qa);
    }
  }
  return res_vector;
}

std::vector<Correlation> Functions::VectorResolutions3S(const Correlation& first,
                                                        const Correlation& second,
                                                        const Correlation& third) {
  std::vector<Correlation> res_vector;
  res_vector.emplace_back(Resolution3S(second, third, first));
  res_vector.emplace_back(Resolution3S(third, first, second));
  res_vector.emplace_back(Resolution3S(first, second, third));

  return res_vector;
}

std::vector<Correlation> Functions::VectorResolutions4S(const Correlation& first,
                                                        const Correlation& second,
                                                        const Correlation& third,
                                                        const Correlation& fourth) {
  std::vector<Correlation> res_vector;
  res_vector.emplace_back(Resolution3S(fourth, first, third));
  res_vector.emplace_back(Resolution4S(first, second, third, fourth));
  res_vector.emplace_back(Resolution3S(fourth, third, first));

  return res_vector;
}
