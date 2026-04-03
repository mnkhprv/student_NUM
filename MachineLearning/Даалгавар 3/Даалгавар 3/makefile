heart:
	python main.py heart_train.tsv heart_test.tsv heart_train_labels.txt heart_test_labels.txt heart_metrics.txt

education:
	python main.py education_train.tsv education_test.tsv education_train_labels.txt education_test_labels.txt education_metrics.txt

all: heart education

clean:
	rm -f heart_train_labels.txt heart_test_labels.txt heart_metrics.txt \
	      education_train_labels.txt education_test_labels.txt education_metrics.txt