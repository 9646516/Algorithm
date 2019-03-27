#include"BerlekampMassey.cpp"
int main() {
	int arr[]= {

	};
	BerlekampMassey::init();
	int n=sizeof(arr)/sizeof(int);
	for (int i=0; i<n; ++i)BerlekampMassey::update(arr[i]);
	printf("Formule: ");
	BerlekampMassey::output();
	printf("Code: \n");
	BerlekampMassey::output_code_for();
	return 0;
}
