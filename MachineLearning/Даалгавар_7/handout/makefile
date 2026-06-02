EPOCHS = 500
LR = 0.1
GLOVE = glove_embeddings.txt

SMALL_OUT = smalloutput
LARGE_OUT = largeoutput
SMALL_IN = smalldata
LARGE_IN = largedata

.PHONY: all small large clean

all: small large

small:
	@mkdir -p $(SMALL_OUT)
	@echo "Running Small Data"
	@python3 feature.py $(SMALL_IN)/train_small.tsv $(SMALL_IN)/val_small.tsv $(SMALL_IN)/test_small.tsv $(GLOVE) \
		$(SMALL_OUT)/train_formatted.tsv $(SMALL_OUT)/val_formatted.tsv $(SMALL_OUT)/test_formatted.tsv
	@python3 lr.py $(SMALL_OUT)/train_formatted.tsv $(SMALL_OUT)/val_formatted.tsv $(SMALL_OUT)/test_formatted.tsv \
		$(SMALL_OUT)/train_labels.txt $(SMALL_OUT)/test_labels.txt $(SMALL_OUT)/metrics.txt $(EPOCHS) $(LR)

large:
	@mkdir -p $(LARGE_OUT)
	@echo "Running Large Data"
	@python3 feature.py $(LARGE_IN)/train_large.tsv $(LARGE_IN)/val_large.tsv $(LARGE_IN)/test_large.tsv $(GLOVE) \
		$(LARGE_OUT)/train_formatted.tsv $(LARGE_OUT)/val_formatted.tsv $(LARGE_OUT)/test_formatted.tsv
	@python3 lr.py $(LARGE_OUT)/train_formatted.tsv $(LARGE_OUT)/val_formatted.tsv $(LARGE_OUT)/test_formatted.tsv \
		$(LARGE_OUT)/train_labels.txt $(LARGE_OUT)/test_labels.txt $(LARGE_OUT)/metrics.txt $(EPOCHS) $(LR)

clean:
	@rm -f $(SMALL_OUT)/train_formatted.tsv \
	      $(SMALL_OUT)/val_formatted.tsv \
	      $(SMALL_OUT)/test_formatted.tsv \
	      $(SMALL_OUT)/train_labels.txt \
	      $(SMALL_OUT)/test_labels.txt \
	      $(SMALL_OUT)/metrics.txt
	@rm -f $(LARGE_OUT)/train_formatted.tsv \
	      $(LARGE_OUT)/val_formatted.tsv \
	      $(LARGE_OUT)/test_formatted.tsv \
	      $(LARGE_OUT)/train_labels.txt \
	      $(LARGE_OUT)/test_labels.txt \
	      $(LARGE_OUT)/metrics.txt