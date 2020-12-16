#ifndef BOOST_MATH_TEST_ISSUE396_DATA_AND_CHECKER_IPP_
#define BOOST_MATH_TEST_ISSUE396_DATA_AND_CHECKER_IPP_

#include <cmath>
#include <cstddef>
#include <limits>

#include <boost/cstdint.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/math/constants/constants.hpp>

namespace boost { namespace math { namespace detail {

const boost::array<std::string, 4U>& test_issue396_control_strings()
{
  // Table[N[Gamma[(1/2) + (10^n)], 503], {n, 0, 3, 1}]

  static const boost::array<std::string, 4U> control_strings =
  {{
    std::string("0.88622692545275801364908374167057259139877472806119356410690389492645564229551609068747532836927233270811341181214128533311807643286221130126254685480139353423101884932655256142496258651447541311446604768963398140008731950767573986025835009509261700929272348724745632015696088776295310820270966625045319920380686673873757671683399489468292591820439772558258086938002953369671589566640492742312409245102732742609780662578082373375752136938052805399806355360503018602224183618264830685404716174941583421211"),
    std::string("1.1332783889487855673345741655888924755602983082751597766087234145294833900560041537176305387276072906583502717008932373348895801731780765775979953796646009714415152490764416630481375706606053932396039541459764525989187023837695167161085523804417015113740063535865261183579508922972990386756543208549178543857406373798865630303794109491220205170302558277398183764099268751365861892723863412249690833216320407918186480305202146014474770321625907339955121137559264239090240758401696425720048012081453338360E6"),
    std::string("9.3209631040827166083491098091419104379064970381623611540161175194120765977611623552218076053836060223609993676387199220631835256331102029826429784793420637988460945604451237342972023988743201341318701614328454618664952897316247603329530308777063116667275003586843755354841307657702809317290363831151480295446074722690100652644579131609996151999119113967501099655433566352849645431012667388627160383486515144610582794470005796689975604764040892168183647321540427819244511610500074895473959438490375652158E156"),
    std::string("1.2723011956950554641822441803774445695066347098655278283939929838804808618389143636393314317333622154343715992535881414698586440455330620652019981627229614973177953241634213768203151670660953863412381880742653187501307209325406338924004280546485392703623101051957976224599412003938216329590158926122017907280168159527761842471509358725974702333390709735919152262756462872191402491961250987725812831155116532550035967994387094267848607390288008530653715254376729558412833771092612838971719786622446726968E2566")
  }};

  return control_strings;
}

template<class BigFloatType>
bool test_issue396_value_checker()
{
  typedef BigFloatType floating_point_type;

  boost::uint32_t ten_pow_n = UINT32_C(1);

  const floating_point_type tol = std::numeric_limits<floating_point_type>::epsilon() * UINT32_C(5000);

  bool result_is_ok = true;

  for(std::size_t i = 0U; i < test_issue396_control_strings().size(); ++i)
  {
    const floating_point_type g = boost::math::tgamma(boost::math::constants::half<floating_point_type>() + ten_pow_n);

    ten_pow_n *= UINT32_C(10);

    using std::fabs;

    const floating_point_type closeness = fabs(1 - (g / boost::lexical_cast<floating_point_type>(test_issue396_control_strings().at(i))));

    result_is_ok &= (closeness < tol);
  }

  return result_is_ok;
}

} } } // namespace boost::math::detail

#endif // BOOST_MATH_TEST_ISSUE396_DATA_AND_CHECKER_IPP_
