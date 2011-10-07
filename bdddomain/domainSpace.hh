#ifndef __BDDDOMAIN_DOMAIN_SPACE_HH__
#define __BDDDOMAIN_DOMAIN_SPACE_HH__

#include <bdddomain/cuddFactory.hh>
#include <bdddomain/domain.hh>
#include <initializer_list>
#include <vector>

namespace MPG { namespace VarImpl {
    
    /**
     * \brief A Domain space object support the domain representation
     * of relations.
     *
     * For now only one object of this class can be created (singleton pattern).
     *
     * Important note: The implementation of this class is based on
     * the implementation present in the JavaBDD framework. Al the
     * credit for its design is to the developers of this package. The
     * package can be downloaded from the website:
     * http://javabdd.sourceforge.net/ . This development is based on
     * that package, the way it abstracts over the different bdd
     * implementations and some of the algorithms presented here are
     * modifications of the ones in the original package.
     */
    class DomainSpace {
    private:
      CUDDBDDFactory factory_;
      std::vector<BDDDomain> columns_;
      int usedVariables;
    public:
      /**
       * \brief Constructs a domain space.
       *
       * The number of columns is set to \a columns and the maximum
       * value that can appear in a column is \a maximum.
       */
      DomainSpace(int columns, int maximum);
      /**
       * \brief Returns a bdd representing the tuple descirbed by the list.
       */
      Bdd represent(std::initializer_list<int> tuple);
      /**
       * \brief Returns a cube with the bdd variables used to represent
       */
      /**
       * \brief Prints \a bdd as a set to \a os.
       */
      void print(std::ostream& os, Bdd& bdd);
      /**
       * \brief Prints the first \a n columns of the set represented by \a bdd.
       */
      void print(std::ostream& os, Bdd& bdd, int n);
    private:
      /**
       * \brief Class to represent a subrange of the elements that
       * have to be printed.
       */
      class OutputBuffer {
	/// Stream where the elements have to be printed at the end
	std::ostream& os_;
	/// Column where the data stored belongs to
	int column_;
	/// Last lowest element inserted
	int lastLow_;
	/// Last highest element inserted
	int lastHigh_;
	/// Whether the buffer is done or not
	bool done;
      public:
	/// Constructor
	OutputBuffer(std::ostream& os, int column);
	/// Append an interval to the buffer
	void append(int low, int high);
	/// Append an element to the buffer
	void append(int low);
	/// Write the information contained in the buffer
	void finish(void);
      };
      /**
       * \brief Helper method for printing a set
       */
      void printSetHelper(OutputBuffer& ob, int value, int i, std::vector<int>& set,
			  std::vector<int> var, int maxSkip);
      /**
       * \brief Helper method for printing \a bdd as a set to \a os.
       */
      void printsetRec(std::ostream& os, Bdd& bdd, std::vector<int>& set, int numCols);
    };
  }}

#endif
