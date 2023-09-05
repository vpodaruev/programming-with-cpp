#!/usr/bin/env python3

import gspread
import re

from urllib.parse import urlparse


_credentials = None
_gc = None


def get_credentials(auth_token):
    global _credentials
    if _credentials is not None:
        return _credentials

    from google.oauth2.service_account import Credentials
    scopes = [
        'https://www.googleapis.com/auth/spreadsheets.readonly'
    ]
    _credentials = Credentials.from_service_account_file(
        auth_token.as_posix(),
        scopes=scopes
    )
    return _credentials


def get_sheet(auth_token):
    """Return client by `auth_token` to get access to Google spreadsheets"""
    global _gc
    if _gc is not None:
        return _gc

    credentials = get_credentials(auth_token)
    _gc = gspread.authorize(credentials)
    return _gc


_gid_pat = re.compile(r"[-\w]{25,}")


def as_id(url):
    """Return ID from Google Drive URL"""
    if _gid_pat.fullmatch(url):  # has ID instead of URL
        return url

    path = urlparse(url).path
    if m := _gid_pat.search(path):
        return m.group(0)

    raise RuntimeError(f"failed to extract ID from URL ({url})")


_gid_frag_pat = re.compile(r"gid=([\d]+)")


def open_worksheet(gc, url):
    """Return worksheet by `url` using client `gc`"""
    gid = 0
    sht = gc.open_by_url(url)
    if m := _gid_frag_pat.search(urlparse(url).fragment):
        gid = int(m.group(1))

    return sht.get_worksheet_by_id(gid)
