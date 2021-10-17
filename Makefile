export AWS_DEFAULT_REGION=us-east-1

deploy-code-test:
	WEBSITE_BUCKET=$$(aws cloudformation describe-stacks \
		--stack-name rdok-test-pioneer0 \
		--query 'Stacks[0].Outputs[?OutputKey==`WebsiteBucket`].OutputValue' \
		--output text); \
	aws s3 sync ./html-build/HTML5 s3://$${WEBSITE_BUCKET} \
		--delete \
		--exclude "*" \
		--include "*.js" \
		--include "*.wasm" \
		--include "*.data" \
		--include "*.html" \
		--include "Utility.js" \
		--include ".htaccess"

deploy-code-prod:
	WEBSITE_BUCKET=$$(aws cloudformation describe-stacks \
		--stack-name rdok-prod-pioneer0 \
		--query 'Stacks[0].Outputs[?OutputKey==`WebsiteBucket`].OutputValue' \
		--output text); \
	aws s3 sync ./html-build/HTML5 s3://$${WEBSITE_BUCKET} \
		--delete \
		--exclude "*" \
		--include "*.js" \
		--include "*.wasm" \
		--include "*.data" \
		--include "*.html" \
		--include "Utility.js" \
		--include ".htaccess"

deploy-infrastructure-test:
	sam deploy \
		--template-file infrastructure.yml \
		--stack-name rdok-test-pioneer0 \
		--s3-bucket "rdok-test-cicd" \
		--s3-prefix "pioneer0" \
		--region "us-east-1" \
		--confirm-changeset \
		--capabilities CAPABILITY_IAM \
		--parameter-overrides \
			DomainName=pioneer0-test.rdok.co.uk \
			Route53HostedZoneId=ZSY7GT2NEDPN0

deploy-infrastructure-prod:
	sam deploy \
		--template-file infrastructure.yml \
		--stack-name rdok-prod-pioneer0 \
		--s3-bucket "rdok-prod-cicd" \
		--s3-prefix "pioneer0" \
		--region "us-east-1" \
		--confirm-changeset \
		--capabilities CAPABILITY_IAM \
		--parameter-overrides \
			DomainName=pioneer0.rdok.co.uk \
			Route53HostedZoneId=ZSY7GT2NEDPN0
