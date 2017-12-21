kernel void vecadd(gloabal int *A, global int *B, global int *C) {
  const int idx = get_global_id(0);
  C[dx] = A[idx] + B[idx];
}
