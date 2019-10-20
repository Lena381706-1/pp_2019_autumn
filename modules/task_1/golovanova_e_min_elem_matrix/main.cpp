// Copyright 2019 Golovanova Elena
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "../../../modules/task_1/golovanova_e_min_elem_matrix/min_elem_matrix.h"

TEST(min_elem_matrix, test1) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    ASSERT_ANY_THROW(getRandomMatrix(-10, 10));
  }
}

TEST(min_elem_matrix, test2) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> M(25);
  for (int i = 1; i < 26; i++)
    M[i] = i;
  int M_min = 1;
  int rez = MinElemMatrix(M, 5, 5);
  if (rank == 0) {
    EXPECT_EQ(rez, M_min);
  }
}



int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  MPI_Init(&argc, &argv);

  ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
  ::testing::TestEventListeners& listeners =
    ::testing::UnitTest::GetInstance()->listeners();

  listeners.Release(listeners.default_result_printer());
  listeners.Release(listeners.default_xml_generator());

  listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
  return RUN_ALL_TESTS();
}
