#include <cptuple/cptuple.hh>

using Gecode::Home;
using Gecode::Space;
using Gecode::Choice;
using Gecode::ExecStatus;
using Gecode::ES_FAILED;
using Gecode::ES_OK;

namespace MPG { namespace CPTuple { namespace Branch {

/**
 * \brief Simple and naive brancher based on tuple inclusion and exclusion.
 * \ingroup RelBranch
 */
class NaiveBranch : public Gecode::Brancher {
protected:
  /// Tuple to branch on
  CPTupleView x_;
  /// Simple, tuple-based relation choice
  class RelChoice : public Gecode::Choice {
  public:
    /// Tuple to branch on
    CPRel::Tuple t_;
    /// Constructor
    RelChoice(const NaiveBranch& b, const CPRel::Tuple& t)
      : Choice(b,2), t_(t) {}
    /// Returns the size of the object
    virtual size_t size(void) const {
      return sizeof(*this);
    }
  };
public:
  /// Constructor for a brancher on variable \a x
  NaiveBranch(Home home, CPTupleView x)
    : Brancher(home), x_(x) {}
  /// Brancher posting
  static void post(Home home, CPTupleView x) {
    (void) new (home) NaiveBranch(home,x);
  }
  /// Constructor for clonning
  NaiveBranch(Space& home, bool share, NaiveBranch& b)
    : Brancher(home,share,b) {
    x_.update(home,share,b.x_);
  }
  /// Brancher copying
  virtual Brancher* copy(Space& home, bool share) {
    return new (home) NaiveBranch(home,share,*this);
  }
  /// Brancher disposal
  virtual size_t dispose(Space& home) {
    (void) Brancher::dispose(home);
    return sizeof(*this);
  }
  /// Returns the status of the brancher
  virtual bool status(const Space&) const {
    if (!x_.assigned())
      return true;
    return false;
  }
  /// Creates a choice by selecting a tuple from the unknown of the variable
  virtual Choice* choice(Space&) {
    TupleSetIter it(x_.domain());
    assert(it());
    return new RelChoice(*this,it.val());
  }
  /// Commit choice
  virtual ExecStatus commit(Space& home, const Choice& c, unsigned int a) {
    const RelChoice& ch = static_cast<const RelChoice&>(c);
    if (a == 0) {
      //std::cout << "-> Brancher assign: " << ch.t_ << std::endl;
      return Gecode::me_failed(x_.assign(home,ch.t_)) ? ES_FAILED : ES_OK;
    } else {
      //std::cout << "-> Brancher removing: " << ch.t_ << std::endl;
      return Gecode::me_failed(x_.exclude(home,ch.t_)) ? ES_FAILED : ES_OK;
    }
  }
};
}}

/**
 * \brief Naive brancher on relation \a R
 * \ingroup RelBranch
 *
 * Branches on \a R by selecting a tuple in it and creating a choice point that
 * includes and excludes that tuple.
 */
void branch(Home home, CPTupleVar t) {
  using namespace CPTuple::Branch;
  if (home.failed()) return;
  NaiveBranch::post(home,t);
}

}
