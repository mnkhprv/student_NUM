PYTHON ?= python3

TRAIN_INPUT := small_train.csv
VALIDATION_INPUT := small_validation.csv
TRAIN_OUT := train_out.txt
VALIDATION_OUT := validation_out.txt
METRICS_OUT := metrics_out.txt
NUM_EPOCH := 2
HIDDEN_UNITS := 4
INIT_FLAG := 2
LEARNING_RATE := 0.1

.PHONY: run test clean

run:
	$(PYTHON) neuralnet.py $(TRAIN_INPUT) $(VALIDATION_INPUT) $(TRAIN_OUT) $(VALIDATION_OUT) $(METRICS_OUT) $(NUM_EPOCH) $(HIDDEN_UNITS) $(INIT_FLAG) $(LEARNING_RATE)

test:
	$(PYTHON) -m unittest tests

clean:
	rm -f $(TRAIN_OUT) $(VALIDATION_OUT) $(METRICS_OUT)
