void* dotProd(void *restrict arg) {

	double * a = ((double**)arg)[0];
	double * b = ((double**)arg)[1];
	free(arg);

	double sum_loc = 0;
	for (size_t ix = 0; ix < block_size; ++ix)
		sum_loc += a[ix]*b[ix];

	pthread_mutex_lock(&mutex_sum);
	sum += sum_loc;
	pthread_mutex_unlock(&mutex_sum);

	return NULL:
}
