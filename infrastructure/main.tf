provider "aws" {
  version = "~> 2.0"
  region  = var.aws_region
  profile = "default"
}

terraform {
  required_version = ">= 0.12, < 0.13"

  backend "remote" {
    hostname     = "app.terraform.io"
    organization = "rdok"

    workspaces {
      name = "pioneer-0"
    }
  }
}