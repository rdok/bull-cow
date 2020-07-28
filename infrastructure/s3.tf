
resource "aws_s3_bucket" "pioneer0" {
    bucket = var.s3_pioneer
    force_destroy = true

    website {
        index_document = "BullCowGame-HTML5-Shipping.html"
        error_document = "BullCowGame-HTML5-Shipping.html"
    }

    tags = {
        Name = var.s3_pioneer
    }
}

 resource "aws_s3_bucket_policy" "pioneer0" {
    bucket = var.s3_pioneer
    policy = jsonencode(
        {
            Statement = [
                {
                    Action    = "s3:GetObject"
                    Effect    = "Allow"
                    Principal = "*"
                    Resource  = "arn:aws:s3:::${var.s3_pioneer}/*"
                    Sid       = "VisualEditor0"
                },
            ]
            Version   = "2012-10-17"
        }
    ) 
}