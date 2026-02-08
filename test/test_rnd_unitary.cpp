//
// Created by Adenilton on 07/02/26.
//

#include <gtest/gtest.h>
#include "../include/randomUnitary.h"

TEST(RND_UNITARY, UNIT8) {
    auto matrix = random_unitary_matrix(8);
    auto identity = matrix * matrix.conjugate().transpose();
    EXPECT_TRUE(identity.isIdentity());
}

TEST(RND_UNITARY, UNIT16) {
    auto matrix = random_unitary_matrix(16);
    auto identity = matrix * matrix.conjugate().transpose();
    EXPECT_TRUE(identity.isIdentity());
}