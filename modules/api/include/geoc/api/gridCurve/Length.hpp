#ifndef GEOC_API_GRIDCURVE_LENGTH_H
#define GEOC_API_GRIDCURVE_LENGTH_H

#include <geoc/estimator/non-adaptable/length/Projected.hpp>
#include <geoc/estimator/non-adaptable/length/SinCos.hpp>
#include <geoc/adapter/base/GeneralAdapter.h>
#include <geoc/adapter/GridCurve.h>

namespace GEOC
{
    namespace API
    {
        namespace GridCurve
        {
            namespace Length
            {
                namespace EstimationAlgorithms
                {
                    template<typename TTangentAdapter>
                    using ALG_PROJECTED = GEOC::Estimator::Standard::ProjectedLength<TTangentAdapter>;

                    template<typename TTangentAdapter>
                    using ALG_SINCOS = GEOC::Estimator::Alternative::SinCosLength<TTangentAdapter>;
                }

                typedef DGtal::Z2i::KSpace KSpace;
                typedef GEOC::Adapter::GridCurve::IteratorType CurveIterator;
                typedef std::vector<double> EstimationsVector;


                template< template<typename> class TAlgorithm>
                void mdssOpen(const KSpace& KImage,
                                   CurveIterator begin,
                                   CurveIterator end,
                                   EstimationsVector& ev,
                                   double h,
                                   void* data)
                {
                    typedef GEOC::Adapter::GeneralAdapter::Identity<CurveIterator,
                            GEOC::Estimator::Standard::MDSSTangent,
                            false> TangentAdapter;
                    TAlgorithm<TangentAdapter>(begin,end,KImage,ev,h,data);
                }

                template< template<typename> class TAlgorithm>
                void mdssClosed(const KSpace& KImage,
                              CurveIterator begin,
                              CurveIterator end,
                              EstimationsVector& ev,
                              double h,
                              void* data)
                {
                    typedef GEOC::Adapter::GeneralAdapter::Symmetric<CurveIterator,
                            GEOC::Estimator::Standard::MDSSTangent,
                            true> TangentAdapter;
                    TAlgorithm<TangentAdapter>(begin,end,KImage,ev,h,data);
                }

                template< template<typename> class TAlgorithm>
                void lmdssOpen(const KSpace& KImage,
                                CurveIterator begin,
                                CurveIterator end,
                                EstimationsVector& ev,
                                double h,
                               void* data)
                {
                    typedef GEOC::Adapter::GeneralAdapter::Identity<CurveIterator,
                            GEOC::Estimator::Alternative::LMDSSTangent,
                            false> TangentAdapter;
                    TAlgorithm<TangentAdapter>(begin,end,KImage,ev,h,data);
                }

                template< template<typename> class TAlgorithm>
                void lmdssClosed(const KSpace& KImage,
                                CurveIterator begin,
                                CurveIterator end,
                                EstimationsVector& ev,
                                double h,
                                 void* data)
                {
                    typedef GEOC::Adapter::GeneralAdapter::Symmetric<CurveIterator,
                            GEOC::Estimator::Alternative::LMDSSTangent,
                            true> TangentAdapter;
                    TAlgorithm<TangentAdapter>(begin,end,KImage,ev,h,data);
                }

            }
        }
    }
}
#endif //GEOC_API_GRIDCURVE_LENGTH_H
