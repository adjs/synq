//
// Created by Adenilton on 03/02/26.
//

#include<iostream>
#include <gtest/gtest.h>
#include "../include/csd.h"
#include "../include/randomUnitary.h"


using namespace std;

TEST(CSD_TEST, Toffoli) {
    Eigen::MatrixXcd T(4, 4);
    T << 1.0 + 0.0i, 0.0 + 0.0i,  0.0 + 0.0i,  0.0 + 0.0i,
         0.0 + 0.0i, 1.0 + 0.0i,  0.0 + 0.0i,  0.0 + 0.0i,
         0.0 + 0.0i, 0.0 + 0.0i,  0.0 + 0.0i,  1.0 + 0.0i,
         0.0 + 0.0i, 0.0 + 0.0i,  1.0 + 0.0i,  0.0 + 0.0i;

    auto out = csd(T, 2, 2);
    auto test_ver = verify(T, out);

    ASSERT_TRUE(test_ver);
}

TEST(CSD_TEST, UNITARY_GATE) {
    Eigen::MatrixXcd T(4, 4);
    T << (2.364882618857422347e-01-4.822143073226670129e-01i),
         (6.829647732695640072e-02+4.447897757628520299e-02i),
         (5.115007388835463020e-01-9.529865837327188005e-02i),
         (5.520571865947265788e-01-3.597469917942807127e-01i),
         (-1.114816726427168281e-01+6.978032089401685623e-01i),
         (-2.494382786327934143e-01+8.410701104345530421e-02i),
         (4.670592911721889728e-01-4.319298125262461818e-01i),
         (1.622065409340211206e-01-1.817602163908954571e-02i),
         (-2.235192632554647840e-01-2.591835234472851801e-01i),
         (2.436499611612899796e-01-5.375622959989125038e-02i),
         (-9.259829400673319499e-02-5.381058778231553319e-01i),
         (2.726770843179722736e-01+6.694197728029507299e-01i),
         (1.151995301476407552e-01-2.859672891120846883e-01i),
         (-9.016492271986602525e-01-2.209918615739195902e-01i),
         (-9.627758278964056171e-02-1.310559524249576557e-01i),
         (-2.001520487551047139e-02+1.276612783179109645e-01i);

    auto out = csd(T, 2, 2);
    auto test_ver = verify(T, out);

    ASSERT_TRUE(test_ver);
}

TEST(CSD_TEST, RND8) {
    auto T = random_unitary_matrix(8);

    auto out = csd(T, 4, 4);
    auto test_ver = verify(T, out);

    ASSERT_TRUE(test_ver);
}

TEST(CSD_TEST, RND16) {
    auto T = random_unitary_matrix(16);

    auto out = csd(T, 8, 8);
    auto test_ver = verify(T, out);

    ASSERT_TRUE(test_ver);
}
