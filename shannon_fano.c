#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
	int freq;
	char symbol;
	char encoding[500];
};

int compareNodes(const void *a, const void *b) {
	struct Node *n1 = (struct Node *) a;
	struct Node *n2 = (struct Node *) b;
	if ((n1->freq - n2->freq) < 0) return -1;
	else if ((n1->freq - n2->freq) > 0) return 1;
	else return 0;
}

void assign_encoding(struct Node* nodes, int left, int right) {
	// printf("left = %d, right = %d\n", left, right);
	if (left == right) return;
	int sum = 0;

	for (int i = left; i <= right; i++) {
		sum += nodes[i].freq;
	}


	int curSum = 0;
	int mid = left;
	while (curSum + nodes[mid].freq <= sum/2 && mid < right) {
		curSum += nodes[mid].freq;
		mid++;
	}

	// an edge case that need to be take care of, where should the middle element go?
	if (mid < right && abs(sum - 2 * (curSum + nodes[mid].freq)) < abs(sum - 2 * curSum)) { 
		curSum += nodes[mid].freq;
		mid++;
	}

	for (int i = left; i < mid; i++) {
		strcat(nodes[i].encoding, "0");
		// nodes[i].encoding = nodes[i].encoding + '1';
	}

	for (int i = mid; i <= right; i++) {
		strcat(nodes[i].encoding, "1");
		// nodes[i].encoding = nodes[i].encoding + '0';
	}

	// printf("left = %d, right = %d, mid = %d, sum = %d\n", left, right, mid, sum);
	assign_encoding(nodes, left, mid - 1);
	assign_encoding(nodes, mid, right);
}

/*
This is the main function
Takes in the number of symbols and the freq of each symbol
*/
void shannon_fano(int n, struct Node* nodes) {
	qsort(nodes, n, sizeof(nodes[0]), compareNodes);

	assign_encoding(nodes, 0, n - 1);
}

int main() {

	struct Node nodes[] = {
		{17, 'a', ""},
		{35, 'b', ""},
		{17, 'c', ""},
		{15, 'd', ""},
		{16, 'e', ""},
	};

	int n = sizeof(nodes) / sizeof(nodes[0]);

	shannon_fano(n, nodes);

	for (int i = 0; i < n; i++) {
		printf("freq = %d, symbol = %c, encoding = %s\n", nodes[i].freq, nodes[i].symbol, nodes[i].encoding);
	}

	return 0;
}