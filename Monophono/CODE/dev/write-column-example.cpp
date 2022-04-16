void scanColumn(int index) {
	for (int i = 0; i < COLUMN_NUMBER; i++) {
		// writeColumn(i, i == index ? HIGH : LOW);
		if (i == index) {
			writeColumn(i, HIGH);
		} else {
			writeColumn(i, LOW);
		}
	}
}

void writeColumn(int index, int value) {
	if (index >= 0 && index < 8) {
		digitalWrite(index, value);
	} else if (index == EXTERNAL_COLUMN) {
		digitalWrite(EXTERNAL, value);
	}
}