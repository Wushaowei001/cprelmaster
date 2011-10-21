#ifndef __CPREL_BDDDOMAIN_ENCODING_HH__
#define __CPREL_BDDDOMAIN_ENCODING_HH__

#include <vector>
#include <obj/cuddObj.hh>
#include <bdddomain/perm-descriptor.hh>

namespace MPG { namespace VarImpl {
    /**
     * \defgroup BDDEnc Ground relation encoding
     *
     *
     */
    /**
     * \brief Creates a cube with all the bdd variables that represent
     * column \a c 
     *
     * \ingroup BDDEnc
     */
    BDD makeCube(int c);
    /**
     * \brief Creates a cube with all the bdd variables that represent
     * columns in \a c
     *
     *\ingroup BDDEnc
     */
    BDD makeCube(const std::vector<int>& c);

    /**
     * \brief Returns the variables (indices) used in the bdd to encode column \a c
     * \ingroup BDDEnc
     */
    std::vector<int> bddIndices(int c);

    /**
     * \brief Returns the variables used in the bdd to encode column \a c
     * \ingroup BDDEnc
     */
    std::vector<DdNode*> bddVars(int c);

    /**
     * \brief Decodes \a cube, extracted from the BDD and returns the tuple it
     * represents.
     * \ingroup BDDEnc
     */
    std::vector<int> decodeCube(int* cube, int arity);

    /**
     * \brief Returns the relation resulting from swapping \a r according to the
     * swapping description \a swapDesc.
     * \ingroup BDDEnc
     * \warning The content of the description is the responsability of the caller.
     */
    BDD swap_columns(BDD r, const PermDescriptor& swapDesc);

    /// Moves all the columns of \a r \a n columns to the left.
    BDD shiftLeft(BDD r, int arity, int n);

    /// Moves all the columns of \a r \a n columns to the right.
    BDD shiftRight(BDD r, int arity, int n);

    /**
     * \brief Discards the columns in the range \a left .. \a right.
     *
     * The way this is done is by moving the columns to the left of the relation and
     * to existentialy quantify on them.
     */
    BDD discard(BDD r, int arity, int left, int right);

    /**
     * \brief Existensial quantification of column \a c on relation \a r.
     * \ingroup BDDEnc
     */
    BDD exists(int c, BDD r);
    /**
     * \brief Existential queantification of all the columns with
     * indices in \a c of relation \a r.
     */
    BDD exists(const std::vector<int>& c, BDD r);

    BDD exists(int first, int last, BDD r);

    /**
     * \brief Universal quantification of column \a c on relation \a r.
     * \ingroup BDDEnc
     */
    BDD forall(int c, BDD r);

    /**
     * \brief Unique quantification of \a r with respect to \a c
     *
     * \a c is assumed to be a cube
     */
    BDD unique(BDD r, BDD c);
    /**
     * \brief Unique quantification of column \a c on relation \a r.
     * \ingroup BDDEnc
     */
    BDD unique(int c, BDD r);

    /**
     * \brief Unique quantification on the columns in \a c on relation \a r.
     * \ingroup BDDEnc
     */
    BDD unique(const std::vector<int>& c, BDD r);

    BDD replace(const std::vector<std::pair<int,int>>& pairing, BDD r);
  }
}
#endif
