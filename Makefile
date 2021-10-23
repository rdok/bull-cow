export AWS_DEFAULT_REGION=us-east-1
################################################################################
# Develop
# Run everytime a new build is ready to be tested or released to production
# Dependency: https://docs.unrealengine.com/en-US/Platforms/HTML5/GettingStarted/index.html
################################################################################
deploy-code-test:
	WEBSITE_BUCKET=$$(aws cloudformation describe-stacks \
		--stack-name rdok-test-pioneer0 \
		--query 'Stacks[0].Outputs[?OutputKey==`WebsiteBucket`].OutputValue' --output text); \
	aws s3 sync ./HTML5 s3://$${WEBSITE_BUCKET} \
		--delete --include "*" --exclude "*.command" --exclude "*.exe" --exclude "*.txt"; \
	DISTRIBUTION_ID=$$(aws cloudformation describe-stacks --stack-name  rdok-test-pioneer0 \
		--query 'Stacks[0].Outputs[?OutputKey==`DistributionID`].OutputValue' --output text); \
	aws cloudfront create-invalidation --distribution-id $${DISTRIBUTION_ID} --paths "/*" --output text


deploy-code-prod:
	TEST_WEBSITE_BUCKET=$$(aws cloudformation describe-stacks --stack-name rdok-test-pioneer0 \
		--query 'Stacks[0].Outputs[?OutputKey==`WebsiteBucket`].OutputValue' --output text); \
	PROD_WEBSITE_BUCKET=$$(aws cloudformation describe-stacks --stack-name rdok-prod-pioneer0 \
		--query 'Stacks[0].Outputs[?OutputKey==`WebsiteBucket`].OutputValue' --output text); \
	aws s3 sync s3://$${TEST_WEBSITE_BUCKET} s3://$${PROD_WEBSITE_BUCKET} --delete
	DISTRIBUTION_ID=$$(aws cloudformation describe-stacks --stack-name  rdok-prod-pioneer0 \
		--query 'Stacks[0].Outputs[?OutputKey==`DistributionID`].OutputValue' --output text); \
	aws cloudfront create-invalidation --distribution-id $${DISTRIBUTION_ID} --paths "/*" --output text

################################################################################
# End Developer
################################################################################

################################################################################
# DevOps: Infrastructure; run once or when it requires changes
################################################################################
deploy-infrastructure-test:
	sam deploy --template-file website-infrastructure.yml --stack-name rdok-test-pioneer0 \
		--s3-bucket "rdok-test-cicd" --s3-prefix "pioneer0" \
		--region "us-east-1" --confirm-changeset --capabilities CAPABILITY_IAM \
		--parameter-overrides \
			DomainName=pioneer0-test.rdok.co.uk \
			Route53HostedZoneId=ZSY7GT2NEDPN0

deploy-infrastructure-prod:
	sam deploy --template-file website-infrastructure.yml --stack-name rdok-prod-pioneer0 \
		--s3-bucket "rdok-prod-cicd" --s3-prefix "pioneer0" \
		--region "us-east-1" --confirm-changeset --capabilities CAPABILITY_IAM \
		--parameter-overrides \
			DomainName=pioneer0.rdok.co.uk \
			Route53HostedZoneId=ZSY7GT2NEDPN0
################################################################################
# End Infrastructure;
################################################################################
